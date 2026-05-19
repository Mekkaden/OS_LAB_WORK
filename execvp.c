#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>



int main(int argc, char *argv[])
{
    // Step 1: Check if two command line arguments are provided
    if(argc != 3)
    {
        printf("Usage: %s num1 num2\n", argv[0]);
        return 1;
    }

    // Step 2: Create a child process using fork()
    pid_t pid = fork();

    // Step 3: Check if fork() failed
    if(pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    // Step 4: If pid == 0 → this is the child process
    else if(pid == 0)
    {
        printf("Child executing myadder\n");

        // Step 5: Prepare argument list for execvp()
        // Format → program_name arg1 arg2 NULL
        char *arg[] = {"./myadder", argv[1], argv[2], NULL}; //read stuff until it hits a null

        // Step 6: Replace child process with myadder program
        execvp(arg[0], arg);

        // Step 7: If execvp() fails, print error
        printf("Exec failed\n");
        return 1;
    }

    // Step 8: If pid > 0 → this is the parent process
    else
    {
        // Step 9: Parent waits for child process to finish
        wait(NULL);
        // Step 10: Print completion message
        printf("Child completed execution\n");
    }

    // Step 11: End of program
    return 0;
}