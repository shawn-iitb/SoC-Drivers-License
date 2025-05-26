# Week 1

You want your driver's license? Not so easily. You have to learn the basics first. In this week, you would go through what an Operating System is. Why? Because drivers are a part of OS and you should understand the OS before driving.

## 1. Process

Read the [Chapter 4](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-intro.pdf) of OSTEP textbook to see what makes up a process and the bookkeeping needed to be done by the OS for the process to run on the cpu.

<b>Achievements and more reading:</b>
 - Memory image of a process - https://tldp.org/LDP/LG/issue23/flower/psimage.html
 - States of a process - https://en.wikipedia.org/wiki/Process_state
 - Data structures used by the OS - https://www.geeksforgeeks.org/process-table-and-process-control-block-pcb/
 - Context switch - https://tldp.org/LDP/LG/issue23/flower/context.html

If you want to learn things in a more linux fashion, you can read the section 4.1 and 4.4 from [here](https://tldp.org/LDP/intro-linux/html/chap_04.html). Feel free to explore other chapters as well.

## 2. Handling processes and Traps

Read the [Chapter 6](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-mechanisms.pdf) from OSTEP textbook to explore the mechanisms used by OS while a process is running, how it restricts a process from doing harmful things, concurrency.

<b>Achievements and more reading:</b>
 - System calls - https://www.geeksforgeeks.org/introduction-of-system-call/
 - List of system calls in linux - https://linasm.sourceforge.net/docs/syscalls/index.php
 - Context Switching - https://linux-kernel-labs.github.io/refs/heads/master/so2/lec3-processes.html#context-switching

Don't be ashamed of reading Linux documentation or even listening to it as an audio book.

## 3. Virtual Address Spaces

For virtualizing the memory, OS uses virtual and physical address spaces. Read Chapter [13](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-intro.pdf) and [14](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-api.pdf) from OSTEP textbook to get a feel of what address spaces are and how user can allocate memory and free it.

<b>Achievements and more reading:</b>
 - Virtual and physical address spaces - https://www.youtube.com/watch?v=DlxuT7Lxzfs This short video will give an idea of address spaces and page tables.

We will cover more of virtual memory in the subsequent weeks.