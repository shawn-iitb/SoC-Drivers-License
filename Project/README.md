# Linux Kernel Programming Assignment

## What are IOCTLs?

IOCTLs (Input/Output Control) are operations performed through the `ioctl()` system call in Unix-like operating systems that provide a way for user-space applications to communicate with device drivers. They allow applications to send commands and data to the kernel, enabling operations that are not covered by standard system calls. IOCTLs are commonly used for device-specific operations, such as configuring hardware devices, reading or writing device-specific data, and controlling device behavior.

Basically, IOCTLs allow us to define custom operations that can be invoked through the `ioctl()` system call, which can be used to perform device-specific operations that are not available through standard system calls like `read`, `write`, or `open`.

## 1. Simple IOCTL call


Make a simple IOCTL call which takes in the pid and VA (Virtual Address) of a user space process and returns the Physical address of the given VA.

Resources:

 -> https://www.opensourceforu.com/2011/08/io-control-in-linux/
 -> https://tldp.org/LDP/lkmpg/2.4/html/x856.html
 -> https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html
 
 And a small example,
 -> https://github.com/pokitoz/ioctl_driver





## 2. Kernel Request Processing System using Circular Buffers & Worker Threads

Make a circular queue which will keep track of the requests and some worker threads which will take up the job of processing from the queue. This is how information received from network cards is also handled in most systems. How to utilize threads in a driver? Hope this video helps in explaining that: https://youtu.be/YfVQt3CD8hk?feature=shared .

Be careful with access to the queue or any data that is shared between the threads. For this use locks and conditional variables wherever required to avoid data race. You can learn more about synchronization from the book Linux Kernel Programming Part 1. Go through Chapter 13. Once you understand why locks are important, you can directly go onto using mutexes in drivers.

---

## Objective

Implement a set of Linux Kernel Modules that collaboratively process dot-product requests from user space using circular buffers and kernel worker threads. This assignment helps deepen your understanding of:

- IOCTL interfaces
- Circular buffer synchronization
- Inter-module communication in the kernel
- Kernel thread creation and management

---

## System Design

You are required to implement **three Linux kernel modules**, each with a defined role:

---

### 1. Device-Reader Module

- Acts as the **entry point** for user-space requests.
- Implements an `ioctl` interface to accept **two integer vectors**.
- Places the request into a **shared circular buffer**.
- Handles queue synchronization using a **mutex** or other locking mechanism.
- Ensures no overwrites when the queue is full (returns `-EAGAIN`).

---

### 2. Device-Worker Module

- Implements one or more **kernel worker threads**.
- Each worker:
  - Fetches requests from the request queue.
  - Computes the **dot product** of the two vectors.
  - Enqueues the result into a **response circular buffer**.
- Threads must use **proper synchronization** on both queues.

---

### 3. Device-Sender Module

- Reads responses from the response buffer.
- Uses `ioctl` to **send the result** back to user space.
- Maps the result to the correct user via a `pid` field in the response.

This is obviously just one such design, feel free to come up with other designs that you think are better (or at least think the tradeoffs are worth it). If you do so, please let us know too.
