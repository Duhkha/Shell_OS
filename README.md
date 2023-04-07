# **DarkShell**

DarkShell is a simple implementation of shell in C. It has some basic functionalities like parsing (tokenizing) the input, piping and running built-in programs or external programs. There is also a little C program called syscall in which we demonstrated how some basic system calls are used.


# **Compiling:**

To compile this shell you will need to install readline library if you don't already have one:

sudo apt-get install libreadline-dev

Clone this repository and use a C compiler to compile the program in order to execute it. Here are the instructions to compile:

gcc -Wall shell.c -o shell -lreadline

Then, carry out the following instruction to start the program:

./shell

After the program has started, you can begin issuing instructions.

For system calls it goes the similar way:

1. gcc -Wall -o syscall syscall.c
2. ./syscall

# **Outline**

1.DarkShell can perform the following commands:

ls

cd

cp

history:

[-r] - prints out history in reverse

fortune:

[-a] - prints out all the quotes

free:

[-b] - prints out memory in bytes

[-m] - prints out memory in megabytes

[-g] - prints out memory in gigabytes

exit

2.DarkShell also can run other external programs and can perform piping

3.System calls:

fork()

wait()

exec()

rfork()

execlp()

forkbomb()

# **Challenges:**

Implementing pipes and knowing how to write a shell in C.   
Implementing the free command required using particular, unknown C functions.   
Complexity issues occasionally arise with our built-in commands.

# **Resources:**

https://pdfcoffee.com/operativni-sistemi-sarajevo-pdf-free.html   
https://www.geeksforgeeks.org/making-linux-shell-c/   
https://www.geeksforgeeks.org/introduction-of-system-call/   
https://stackoverflow.com/questions/20447187/c-linux-shell-repeat-the-recent-commands   
https://www.geeksforgeeks.org/c-program-copy-contents-one-file-another-file/   
https://www.geeksforgeeks.org/fork-bomb/   
https://stackoverflow.com/questions/349889/how-do-you-determine-the-amount-of-linux-system-ram-in-c   
https://www.theurbanpenguin.com/4184-2/   
https://stackoverflow.com/questions/20974717/why-does-read-have-to-be-a-system-call-run-in-kernel-mode


## **Authors/contacts:**

Merima Maksumic   merima.maksumic@stu.ibu.edu.ba

Ismar kovacevic   ismar.kovacevic@stu.ibu.edu.ba


# **Warning**
Using arrow keys to search for previous commands is enabled but it does result in prompt getting erased. We didn't have time to fix that. Reasons for that might be becuase of our way of printing out the prompt. Possible solution snprintf(). 

Also if we had more time we would implement redirecting, which we did use in our previous version of this shell. In this version we focused more on piping.


#1.5 TASK

#Q1:Do the following actions require the OS to use kernel mode or user mode is sufficient?
1. A program wants to read from disk.
2. Reading the current time from the hardware clock.

Since reading from disk involves hardware access and privileged instructions that can only be performed by the operating system, kernel mode must be used. To request the data from the disk, the software would need to send a system call to the kernel. The kernel would then conduct the I/O operation on the program's behalf.


Depending on the hardware and operating system configuration, reading the current time from the hardware clock can be done either in user mode or kernel mode. On some systems, reading the clock might call for a context transition to kernel mode and a system call to the kernel. Other systems might have a memory-mapped hardware register that allows user mode access to the clock without a system call or context switch. However, access to kernel mode would be necessary to change the clock or adjust the system time.


#Q2:

A user-level software can request a service from the operating system kernel using a system call. A system call must be used by a program to ask the operating system to carry out a task on its behalf when the task calls for privileged access, hardware access, or interaction with system resources.


There are several categories of system calls, including:

Process control: These system calls allow a program to create, manipulate, and terminate processes. 

Examples include:

fork(): creates a new process by duplicating the calling process
exec(): replaces the current process image with a new process image
wait(): waits for a child process to terminate





File management: These system calls are used to create, modify, and delete files and directories. 

Examples include:

open(): opens a file for reading, writing, or both
read(): reads data from a file
write(): writes data to a file

Device management: These system calls allow a program to interact with hardware devices, such as printers and network cards.
 
Examples include:

ioctl(): controls the operation of a device
read(): reads data from a device
write(): writes data to a device

Information maintenance: These system calls provide access to system information, such as the system time and user account information. 

Examples include:

gettimeofday(): retrieves the current time of day
getuid(): retrieves the user ID of the current process
getpid(): retrieves the process ID of the current process

Communication: These system calls allow processes to communicate with each other, either locally or over a network. 

Examples include:

socket(): creates a network socket
send(): sends data over a network connection
recv(): receives data over a network connection

Although the individual system calls offered by a given operating system may differ, they typically fit into these categories.




