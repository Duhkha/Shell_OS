#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sched.h>

int main() {
    int choice;
    while (1) {
        printf("\033[1;34m");
        printf("Enter a number to choose a function to run:\n");
        printf("1. fork(), wait(), and exec()\n");
        printf("2. rfork()  - Doesnt work\n");
        printf("3. execlp()\n");
        printf("4. forkbomb\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                return 0;
            case 1:
                printf("Basic system calls: \n");
                basic_sys_calls();
                break;
            case 2:
                printf("rfork(): \n");
                rfork_example();
                break;
            case 3:
                printf("execlp: \n");
                execlp_example();
                break;
            case 4:
                printf("forkbomb: \n");
                forkbomb_example();
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}





void basic_sys_calls() {
    printf("\033[1;31m");
    printf("Hello world! (pid: %d)\n", (int) getpid());
    int rc = fork();

    if (rc < 0) {
        // fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("Hello world! From child (pid: %d)\n", (int)getpid());
        char *args[3];
        args[0] = strdup("ls");
        args[1] = strdup("-a");
        args[2] = NULL;
        execvp(args[0], args);
        printf("This line should not be printed\n");
    } else {
        // parent process
        int wc = wait(NULL); // wait for child to be executed
        printf("Hello world! I am the parent process (pid: %d) with a child process (pid: %d), and the value returned by the child process is: %d\n", (int)getpid(), rc, wc);
    }
}

void rfork_example() {
}
    



void execlp_example() {
    printf("\033[1;32m");
    printf("Starting execlp()...\n");

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // This is the child process
        if (execlp("ls", "ls", "-l", NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    } else {
        // This is the parent process
        int status;
        waitpid(pid, &status, 0);
        printf("Child process finished\n");
    }
}


void forkbomb_example() {
    while (1) {
            fork();
        }
}



