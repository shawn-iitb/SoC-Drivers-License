#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define MAX_CWD_SIZE 256
#define MAX_BG_TASKS 64
#define MAX_FG_TASKS 64

int fg_tasks[MAX_FG_TASKS] = {-1};
int breakdown = 0;

/* Splits the string by space and returns the array of tokens
*
*/
void tokenize(const char *line, char **tokens) {
    char token[MAX_TOKEN_SIZE];
    int tokenIndex = 0, tokenNo = 0;

    for (int i = 0; i < strlen(line); i++) {
        const char readChar = line[i];

        if (readChar == ' ' || readChar == '\n' || readChar == '\t') {
            token[tokenIndex] = '\0';
            if (tokenIndex != 0) {
                tokens[tokenNo] = (char *) malloc(MAX_TOKEN_SIZE * sizeof(char));
                strcpy(tokens[tokenNo++], token);
                tokenIndex = 0;
            }
        } else {
            token[tokenIndex++] = readChar;
        }
    }

    tokens[tokenNo] = NULL;
}

void free_tokens(char **tokens) {
    // Freeing the allocated memory
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
        tokens[i] = NULL;
    }
}

void child(char **tokens, const int start, const int end, const int fg, int pipes[][2], const int num_pipes, int io[]) {
    if (!fg) {
        setpgid(0, 0);
    }
    signal(SIGINT, SIG_DFL); // shdnt actually matter since the handler doesn't go through exec()

    // managing all pipes
    for (int i = 0; i < num_pipes; i++) {
        if (pipes[i][0] == io[0]) {
            dup2(io[0], STDIN_FILENO);
        } else {
            close(pipes[i][0]);
        }


        if (pipes[i][1] == io[1]) {
            dup2(io[1], STDOUT_FILENO);
        } else {
            close(pipes[i][1]);
        }
    }

    // making the ending NULL and exec() (safe to change tokens since it is the child process copy)
    free(tokens[end]);
    tokens[end] = NULL;
    execvp(tokens[start], tokens + start);
    printf("Error: command not found\n");

    exit(1);
}

void special_cmd_cd(char **tokens, const int start, const int end) {
    if (end - start != 2) {
        printf("Syntax: cd <directory name>\n");
        breakdown = 1;
        return;
    }

    const char *path = tokens[start + 1];

    if (chdir(path) == -1) {
        printf("Error: Invalid path\n");
        breakdown = 1;
    }
}

void special_cmd_exit(int bg_tasks[], char **tokens) {
    // killing all bg tasks
    for (int i = 0; bg_tasks[i] != -1; i++) {
        kill(bg_tasks[i], SIGKILL);
    }

    // waiting for all bg tasks
    for (int i = 0; bg_tasks[i] != -1; i++) {
        waitpid(bg_tasks[i], NULL, 0);
    }

    free_tokens(tokens);
    exit(0);
}

void die(char cmd[], char error[]) {
    printf("Error: %s cannot be %s\n", cmd, error);
    breakdown = 1;
}

void pip_command(char **tokens, const int start, const int end, int bg_tasks[], const int fg, const int prl, int pipes[][2], const int num_pipes, int io[]) {
    if (tokens[start] == NULL) {
        return;
    }

    if (strcmp(tokens[start], "exit") == 0) {
        if (prl) {
            die("exit", "run in parallel with another command");
            return;
        }
        if (num_pipes > 0) {
            die("exit", "used with pipes");
            return;
        }
        special_cmd_exit(bg_tasks, tokens);
    }

    if (strcmp(tokens[start], "cd") == 0) {
        if (prl) {
            die("cd", "run in parallel with another command");
            return;
        }
        if (num_pipes > 0) {
            die("cd", "used with pipes");
            return;
        }
        special_cmd_cd(tokens, start, end);
        return;
    }

    const int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        child(tokens, start, end, fg, pipes, num_pipes, io);
        exit(0);
    }


    if (fg) {
        // appending task to fg_tasks
        for (int i = 0; i < MAX_FG_TASKS; i++) {
            if (fg_tasks[i] == -1) {
                fg_tasks[i] = rc;
                fg_tasks[i + 1] = -1;
                break;
            }
        }
    } else {
        printf("Shell: Background process started: %d\n\n", rc);

        // appending task to bg_tasks
        for (int i = 0; i < MAX_BG_TASKS; i++) {
            if (bg_tasks[i] == -1) {
                bg_tasks[i] = rc;
                bg_tasks[i + 1] = -1;
                break;
            }
        }
    }
}

void prl_command(char **tokens, const int start, const int end, int bg_tasks[], const int fg, const int prl) {
    if (tokens[start] == NULL) {
        return;
    }

    int num_pipes = 0;
    for (int i = start; i < end; i++) {
        if (strcmp(tokens[i], "|") == 0) {
            num_pipes++;
        }
    }

    // making pipes
    // if (num_pipes > 0) {
    int pipes[num_pipes][2];
    for (int i = 0; i < num_pipes; i++) {
        pipe(pipes[i]);
    }

    // making ios for each process
    int ios[num_pipes + 1][2];
    ios[0][0] = STDIN_FILENO;
    for (int i = 0; i < num_pipes; i++) {
        ios[i][1] = pipes[i][1];
        ios[i + 1][0] = pipes[i][0];
    }
    ios[num_pipes][1] = STDOUT_FILENO;

    // executing every command in pipe
    for (int i = start, idx = 0, starter = start;; i++) {
        if (i == end) {
            pip_command(tokens, starter, i, bg_tasks, fg, prl, pipes, num_pipes, ios[idx]);
            break;
        }
        if (strcmp(tokens[i], "|") == 0) {
            pip_command(tokens, starter, i, bg_tasks, fg, prl, pipes, num_pipes, ios[idx]);
            idx++;
            starter = i + 1;
        }
    }

    // closing all pipes
    for (int i = 0; i < num_pipes; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

void srl_command(char **tokens, const int start, int end, int bg_tasks[]) {
    if (tokens[start] == NULL) {
        return;
    }

    // checking if background task
    int fg = 1;
    if (strcmp(tokens[end - 1], "&") == 0) {
        end--;
        fg = 0;
    }

    // executing every command in parallel
    int prl = 0;
    for (int i = start, starter = start;; i++) {
        if (i == end) {
            prl_command(tokens, starter, i, bg_tasks, fg, prl);
            break;
        }
        if (strcmp(tokens[i], "&&&") == 0) {
            prl = 1;
            prl_command(tokens, starter, i, bg_tasks, fg, prl);
            starter = i + 1;
        }
    }

    for (int i = 0; i < MAX_FG_TASKS && fg_tasks[i] != -1; i++) {
        const int pid = fg_tasks[i];

        int ws;
        waitpid(pid, &ws, 0);

        fg_tasks[i] = -1;

        const int exit_status = WEXITSTATUS(ws);
        if (exit_status == 1) {
            printf("EXITSTATUS: 1 [%d]\n", pid);
            breakdown = 1;
        }
    }
}

void handler(const int sig) {
    if (sig != 2) {
        fprintf(stderr, "Error: handler called with signal %d\n", sig);
    }

    breakdown = 1;
}

int main(int argc, char *argv[]) {
    char line[MAX_INPUT_SIZE];
    char *tokens[MAX_NUM_TOKENS] = {};

    // background tasks stuff
    int bg_tasks[MAX_BG_TASKS];
    bg_tasks[0] = -1;

    signal(SIGINT, handler);

    while (1) {
        /* BEGIN: TAKING INPUT */
        bzero(line, sizeof(line));

        char cwd[MAX_CWD_SIZE];

        getcwd(cwd, MAX_CWD_SIZE);
        printf("%s $ ", cwd);
        scanf("%[^\n]", line);
        getchar();

        // printf("Command entered: %s (remove this debug output later)\n", line);
        /* END: TAKING INPUT */

        free_tokens(tokens);

        line[strlen(line)] = '\n'; //terminate with new line
        tokenize(line, tokens);

        //do whatever you want with the commands, here we just print them

        // starting with no breakdown
        breakdown = 0;

        // executing every command in series
        for (int i = 0, start = 0; !breakdown; i++) {
            if (tokens[i] == NULL) {
                srl_command(tokens, start, i, bg_tasks);
                break;
            }
            if (strcmp(tokens[i], "&&") == 0) {
                srl_command(tokens, start, i, bg_tasks);
                start = i + 1;
            }
        }


        // managing background tasks
        for (int i = 0, j = 0; i < MAX_BG_TASKS; i++, j++) {
            if (bg_tasks[i] == -1) {
                bg_tasks[j] = -1;

                break;
            }

            const int pid = bg_tasks[i];

            int ws;
            const int return_pid = waitpid(pid, &ws, WNOHANG);


            if (return_pid == pid) {
                printf("\nShell: Background process finished: %d\n", pid);

                const int exit_status = WEXITSTATUS(ws);
                if (exit_status == 1) {
                    printf("EXITSTATUS: 1\n");
                }
                j--;
            } else {
                bg_tasks[j] = bg_tasks[i];
            }
        }
    }
}
