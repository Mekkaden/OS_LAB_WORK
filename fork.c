#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if(pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if(pid == 0)
    {
        printf("Child Process\n");
        printf("PID : %d\n", getpid());
        printf("PPID : %d\n", getppid());
    }
    else
    {
        printf("Parent Process\n");
        printf("PID : %d  PPID : %d\n", getpid(), getppid());
    }

    return 0;
}