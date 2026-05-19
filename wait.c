#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        exit(1);
    }

    if (pid == 0)
    {
        printf("Child Process\n");
        printf("PCCSL407\n");
    }
    else
    {
        wait(NULL);
        //When the Parent process hits that line of code, it completely freezes its own execution. 
        //It goes to sleep and tells the Operating System: "Do not wake me up until my Child process has finished executing and is completely dead."
        printf("Parent Process\n");
        printf("OS lab\n");
    }

    return 0;
}