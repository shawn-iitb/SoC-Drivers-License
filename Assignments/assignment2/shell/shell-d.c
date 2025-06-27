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

/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line) {
    char **tokens = (char **) malloc(MAX_NUM_TOKENS * sizeof(char *));
    char *token = (char *) malloc(MAX_TOKEN_SIZE * sizeof(char));
    int i, tokenIndex = 0, tokenNo = 0;

    for (i = 0; i < strlen(line); i++) {
        char readChar = line[i];

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

    free(token);
    tokens[tokenNo] = NULL;
    return tokens;
}

void free_tokens(char **tokens) {
    // Freeing the allocated memory
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

void child(char **tokens) {
    execvp(tokens[0], tokens);
    printf("Error: command not found\n");
    free_tokens(tokens);
    exit(1);
}

void special_cmd_cd(char **tokens) {
    if (tokens[1] == NULL || tokens[2] != NULL) {
        printf("Syntax: cd <directory name>\n");
        return;
    }

    char *path = tokens[1];

    chdir(path);
}


int main(int argc, char *argv[]) {
    char line[MAX_INPUT_SIZE];
    char **tokens;


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

        line[strlen(line)] = '\n'; //terminate with new line
        tokens = tokenize(line);

        //do whatever you want with the commands, here we just print them

        if (tokens[0] == NULL) {
            free_tokens(tokens);
            continue;
        }

        if (strcmp(tokens[0], "cd") == 0) {
            special_cmd_cd(tokens);
            free_tokens(tokens);
            continue;
        }

        if (strcmp(tokens[0], "exit") == 0) {
            free_tokens(tokens);
            break;
        }



        int rc = fork();
        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
        } else if (rc == 0) {
            child(tokens);
            free_tokens(tokens);
            exit(0);
        }

        int ws;

        wait(&ws);

        int exit_status = WEXITSTATUS(ws);
        if (exit_status == 1) {
            printf("EXITSTATUS: 1\n");
        }


        // for(i=0;tokens[i]!=NULL;i++){
        //     printf("found token %s (remove this debug output later)\n", tokens[i]);
        // }
        free_tokens(tokens);
    }
    return 0;
}
