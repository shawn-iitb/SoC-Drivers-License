#  Linux Keyboard Driver Hacking Projects

This repository documents a series of progressively more complex experiments with the Linux PS/2 keyboard driver (`atkbd.c`). These are meant to be educational, safe experiments done in **VirtualBox** or any virtual machine running a custom-compiled Linux kernel.

 ### ⚠️ These are for educational purposes only. Moreover, do **NOT** deploy on your own systems. Only test in VMs.

---

## 1. Cursed Keyboard: Offset All Keypresses

The goal is to change all keyboard input so that every character is random.

The file of interest is `drivers/input/keyboard/atkbd.c`. But which function do we modify? Have a look around to figure out!
‎
<details>
<summary>Psst.. want a hint?</summary>
 
      So, when you press a key, somehow your driver has to get the data right? Maybe try seraching for the function which receives the data?
</details>
‎
<details>

<summary>Still feel stuck?</summary>

   Look for the function:

   ```c
   static irqreturn_t atkbd_receive_byte(...)
   ```
</details>
   ‎

After you've made changes, rebuild and restart the kernel.

To do so, run these commands:
   ```bash
   make -j$(nproc) # splits it into n jobs
   sudo make modules_install
   sudo make install
   sudo update-grub
   sudo reboot
   ```
---

## 2. Simple Keylogger (Kernel Logging)

The goal is to log every keypress scancode to the kernel log (`dmesg`). Look up `printk` to figure out how to write to kernel log! Use a custom message so that you can later use grep to extract relevant information.


After you've made the changes rebuild, reboot, and run:
   ```bash
   dmesg | grep keylogger
   ```

**Note:** Look up `man dmesg` if you want to what exactly dmesg does 

---

## 3. Advanced: Log to File + Frequency Counter

The goal is to:
- Record keys into a file
- Count frequency of each key
- Optionally detect keywords (like `sudo`, `password`)

Some useful functions to write to files from the kernel would be `kernel_write`, `flip_open` and `flip_close`(don't forget to close files you've opened!).

These open calls return a pointer in memory to which if you write, you write to the file as well. It returns an object of type `struct file *`


**NOTE:** Writing to files from the kernel is tricky and not recommended in production — but is useful for learning.

---

## Optional Shortcut Injection: Clear Terminal on F5 Keypress

The goal is this. When the user presses the `F5` key, automatically inject the `clear` command followed by Enter — as if the user typed it — directly from the kernel.

A few functions of interest would be `input_report_key` and `input_sync`. The first function simulates key presses and releases. `input_sync` marks a batch of such signals as complete to be sent to the user. This is similar to how in `cout`, we have flush - this ensure we see the things printed then and there.

**NOTE:** Keystrokes are defined as macros in `input-event-codes.h`. So you might want to check that out.

Recompile and reboot as usual. Now pressing `F5` should clear the terminal.

Note that this works in TTYs and simple terminals like `xterm`, but not always in graphical input environments (like Wayland). 

## References

- [Linux Input Subsystem Docs](https://www.kernel.org/doc/html/latest/input/)
- [Linux Device Drivers, 3rd Edition](https://lwn.net/Kernel/LDD3/)
- `input_event` structure and `atkbd.c` driver code

---

## Disclaimer(ONCE AGAIN)

**Modifying keyboard drivers can crash your system or lock out input. Always keep a fallback kernel and test in a virtual machine only.**

---


