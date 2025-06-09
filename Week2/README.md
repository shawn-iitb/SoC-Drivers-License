# Week 2

I hope by now you are familiar with a lot of basic terminology and have a high level understanding of some components of Operating Systems and have a basic idea about different abstractions. This week we will dive a little deeper into some of the things you read about in the last week.

## 1. System Calls

So from last week I assume you an idea about what system calls are and the names of different system calls and their use cases, now we will dive a little deeper into these system calls one-by-one. To start with [Chapter 5](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf) is a good way to get a basic idea about the fork, exec and wait system calls and this can be supplemented with the resources below. 

<b> Fork System Call </b>
- So first of all you can read up basic terminologies about fork at https://www.geeksforgeeks.org/fork-system-call-in-operating-system/ and https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html and some code examples on how to use it at https://www.geeksforgeeks.org/fork-system-call/
-  Ever wondered what is underneath the hood of `fork()` ? If you are courageous enough (seriously) you can look up the help-routines for it at https://github.com/torvalds/linux/blob/master/kernel/fork.c .This is definitely very daunting and you can look at the comments in the file to understand what section does what. 
-  Easily possible you would have skipped that completely, Linux is a very complex operating system supporting numerous functionalities, still to get a high level overview of what all is necessary at a basic level to implement the `fork()` system call, you can look at Page 34 and 35 (from line 2580 to 2621) from https://www.cse.iitb.ac.in/~mythili/os/references/xv6-rev11.pdf .This contains code from xv6 operating system, which is much simpler compared to Linux. This should give some intuition about what are necessary things to do while creating a new process. There are a lot of things which you might not get at the moment, but don't worry things will get simpler with time.
  
<b>Exit System Call</b>
- Again you can read about it from https://www.geeksforgeeks.org/c-exit-abort-and-assert-functions/ and https://en.wikipedia.org/wiki/Exit_(system_call)
- The xv6 code for `exit()` can be found at Page 35 of the same pdf.
- The Linux implementation can be seen at https://github.com/torvalds/linux/blob/master/kernel/exit.c and https://github.com/torvalds/linux/blob/master/kernel/exit.h

<b>Wait System Call</b>
- Read about the wait system call and look at some code examples from https://www.geeksforgeeks.org/wait-system-call-c/ and https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/wait.html .Do pay attention to the different variants of it like `waitpid()`.
- xv6 implementation can be found at Pages 35 and 36 
- The Linux implementation is spread across a number of files, majority being in the exit.c file where functions `do_wait()` and `do_waitpid()`. Some declarations are also in the exit.h file you saw previously and https://github.com/torvalds/linux/blob/master/include/linux/wait.h

<b>Exec System Call</b>
- The exec system call is not one system call but a family of system calls. You can read about it and look at the examples of different variants https://en.wikipedia.org/wiki/Exec_(system_call)#:~:text=In%20computing%2C%20exec%20is%20a,referred%20to%20as%20an%20overlay. and  https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/exec.html and https://www.geeksforgeeks.org/exec-family-of-functions-in-c/
- For xv6 implementation look at Page 75, this would look a lot complicated than the previous ones so don't get intimidated, the main point is to just get you to start thinking about the various nuances of different system calls.
- The exec family system calls are implemented around the implemented in the Linux kernel primarily through the `execve()` system call. The primary implementation is present in https://github.com/torvalds/linux/blob/master/fs/exec.c .For loading the ELF binaries the loader is implemented in https://github.com/torvalds/linux/blob/master/fs/binfmt_elf.c .The structure declarations are present in https://github.com/torvalds/linux/blob/master/include/linux/binfmts.h

## 2. Shell

Now you must have got a good understanding of the system calls. Ever wondered how things work when you type commands like `ls`, `echo`, `cat` etc? After bootup, the init process is first process created which then spawns a shell like bash. All future processes are created by forking from existing processes like init or shell. The shell reads user command, forks a child, execs the command executable, waits for it to finish, and reads next command. But do note that all commands do not exist as executables. Common commands like `ls`, `echo`, `cat`, are all readily available executables that are simply exec-ed by the shell. This is a high level idea on the working of a shell.
Just think over this : why does the shell fork a child to exec the command? Why does it not directly exec the command?
You can read more about shell, foreground and background execution and I/O redirection from :
- https://www.scaler.com/topics/shell-in-operating-system/
- https://teaching.healthtech.dtu.dk/unix/index.php/Processes%3B_foreground_and_background,_ps,_top,_kill,_screen,_nohup_and_daemons
- https://www.geeksforgeeks.org/input-output-redirection-in-linux/

## 3. Signals

Signal are a way to send notifications to processes. Standard signals are available in operating systems, each corresponding to a specific event, and with a specific signal number for example you would remember typing Ctrl+C to end a running process or close the terminal with Ctrl+D right? They are formally SIGINT and SIGSTP (the specific signals for these events). 
So now the natural question arises, how do I send a signal to a process? System Calls come to the rescue again! The system call kill can be used to send a signal from one process to other.Remember, names can be misleading. The kill system call can send all signals, not just SIGKILL. There are some restrictions on who can send to whom for isolation and security and signals can also be generated by OS for a process, e.g., when it handles 
interrupt due to Ctrl+C keyboard event.
Note that you can overwrite the default behaviour of some signals by writing a custom signal handler. In simple terms now when the process receives that signal, it will perform actions which the signal handle wants it to than the default one. Question : What advantages do we get by this ? You can communicate between processes now!
The following resources are describe signals, signal handlers and how you can use them like sending a signal to a group of processes :
- https://www.geeksforgeeks.org/signal-handling-in-linux-through-the-signal-function/
- https://faculty.cs.niu.edu/~hutchins/csci480/signals.htm
- https://mitu.co.in/wp-content/uploads/2017/09/Signal-Handling-in-Linux.pdf
- https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-setpgid-set-process-group-id-job-control
  
## 4. User Mode and Kernel Mode
Modern operating systems, including Linux, operate in two distinct modes of execution: User Mode and Kernel Mode. These modes provide a foundation for system security, stability, and efficient resource management by enforcing privilege separation between applications and the core of the operating system.
User Mode is where regular applications (like browsers, text editors, and shells) run. These processes are restricted — they cannot directly access hardware or memory of other processes.
Kernel Mode is where the operating system core runs. Code running in this mode (like device drivers, schedulers, and system call handlers) has full access to the system's hardware and memory.
This distinction is crucial for system protection: when a user program needs to access protected resources (e.g., file systems or hardware devices), it must make a system call, which transitions the CPU from User Mode to Kernel Mode.
Some more details :
- https://en.wikipedia.org/wiki/User_space_and_kernel_space
- https://www.geeksforgeeks.org/user-mode-and-kernel-mode-switching/
- https://www.geeksforgeeks.org/difference-between-user-mode-and-kernel-mode/
- https://www.tutorialspoint.com/User-Mode-vs-Kernel-Mode



## Ending Points

- If you feel any difficulty in understanding some of the concepts or are interested in learning things in more details you can have a look at the video lectures from [here](https://www.youtube.com/@johnkubiatowicz3737). This is a very detailed series of video lectures on Operating Systems, but some parts may need more pre-requisites like Computer Architecture, so right now I would advice to just go through the relevant things or you may end up being more confused. 
- There exist a lot of different options and variants in system calls. MAN pages come to your rescue here. It would be a good habit to open the man pages of these system calls and explore the functionality you can get from different options (the command would be `man 2 <syscall name>`) like `man 2 fork` or `man 2 exit`. This will teach you to learn looking at documentations and references while coding in general than using LLMs for direct help (using man pages will train you for your lab exams atleast).
