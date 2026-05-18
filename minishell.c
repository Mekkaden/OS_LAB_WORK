#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#define MAX_CMD 1024
#define MAX_ARGS 64
int main()
{
char command[MAX_CMD];
char *args[MAX_ARGS];
while (1)
{
printf("minishell>");
fgets(command, MAX_CMD, stdin);
command[strcspn(command,"\n")] = 0;
if(strcmp(command,"exit")==0)
	break;
int background = 0;
char *token = strtok(command," ");
int i = 0;
while(token != NULL)
{
args[i++] = token;
token = strtok(NULL," ");
}

args[i] = NULL;
if(i>0 && strcmp(args[i-1],"&")==0)
{
background = 1;
args[i-1] = NULL;
}
pid_t pid = fork();
if(pid<0)
{
printf("Fork failed\n");
return 1;
}
if(pid == 0)
{
execvp(args[0], args);
perror("Execution failed");
exit(1);
}
else
{
if(!background)
wait(NULL);
}
}
printf("Exiting shell\n");
return 0;
}
