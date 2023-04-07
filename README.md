# **DarkShell**

DarkShell is a simple implementation of shell in C. It has some basic functionalities like parsing(tokenizing) the input,piping and running built-in programs or external programs.


# **Compiling:**

To compile this shell you will need to install readline library if you don't already have one:
sudo apt-get install libreadline-dev

Clone this repository and use a C compiler to compile the program in order to execute it. Here are the instructions to compile:

gcc -Wall shell.c -o shell -lreadline

Then, carry out the following instruction to start the program:

./shell

After the program has started, you can begin issuing instructions.

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
    execle()
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







