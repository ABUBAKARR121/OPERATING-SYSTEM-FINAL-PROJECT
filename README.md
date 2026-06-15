Sierra Leone OS  SLeOS
========================

Limkokwing University 2026

A minimal bootable operating system prototype built for educational purposes.
It runs on QEMU and demonstrates core OS concepts.

What is SLeOS
-------------

SLeOS is a custom operating system written in C and Assembly.
It includes a process scheduler, memory manager, in memory file system,
interactive shell, and login system.

The project addresses local computing challenges in Sierra Leone
and supports SDGs 4, 9, and 10.

Features
--------

Custom bootloader (Multiboot compliant)
Process scheduler (FCFS plus Round Robin simulation)
Memory manager (Paging simulator with visual output)
Virtual file system (256 files, up to 4KB each)
Interactive shell (help, create, read, write, delete, logo, reboot)
Login system (username: sleos, password: 1234)
CP437 box art logo with Sierra Leone flag colours

Project Structure
-----------------

SLeOS

* bootloader         Assembly bootloader
* kernel
  * core             kernel.c, login.c, system.h
  * drivers
    * display        vga.c/h, console.c/h
    * input          keyboard.c/h
  * proc             process.c/h, scheduler.c/h
  * mem              paging.c/h, memory.c/h
  * fs               file.c/h, vfs.c/h
  * shell            commands.c/h, shell.c/h
* libc               string.c/h, stdio.c/h
* Makefile           Build automation
* linker.ld          Linker script

Prerequisites
-------------

You need the following tools installed on your Ubuntu system:

* nasm
* gcc (multilib support)
* ld
* grub-mkrescue (and xorriso)
* qemu-system-x86

Install them with:

    sudo apt update
    sudo apt install nasm gcc-multilib grub-pc-bin grub-common xorriso qemu-system-x86 mtools

How to Build
-------------

1. Open a terminal and enter the project directory:

    cd SLeOS

2. Build the ISO image:

    make

   This compiles all source files, links the kernel, and creates sles.iso.

3. To clean previous builds:

    make clean

How to Run
----------

After building, start SLeOS with:

    make run

This will launch QEMU and boot the operating system.

Credentials
-----------

Username: sleos
Password: 1234

Available Commands
------------------

help          Show command reference
clear         Clear the screen
ps            List running processes
mem           Show memory usage
ls            List files
create name   Create a new file
cat name      Read a file (also read or type)
write name text  Write text to a file (multiple words allowed)
delete name   Delete a file (also del or rm)
logo          Redisplay the welcome banner
reboot        Restart the system
about         About SLeOS
sysinfo       System information

Example Session
---------------

SLeOS> help
SLeOS> ls
SLeOS> cat README.TXT
SLeOS> create myfile.txt
SLeOS> write myfile.txt Hello this is a test
SLeOS> cat myfile.txt
SLeOS> mem
SLeOS> ps
SLeOS> logo
SLeOS> reboot

License
-------

This project is distributed under the MIT License.
See the LICENSE file for details.

SDG Alignment
-------------

SDG 4  Quality Education
SDG 9  Industry, Innovation and Infrastructure
SDG 10 Reduced Inequalities

Acknowledgements
----------------

Developed by Limkokwing University students as part of the
Operating Systems module, 2026 academic year.
