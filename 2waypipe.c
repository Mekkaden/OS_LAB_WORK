#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd1[2], fd2[2];
    char str[100], rev[100];

    pipe(fd1); // parent -> child
    pipe(fd2); // child -> parent

    int pid = fork();

    if (pid > 0) {
        // ----- PARENT -----

        printf("Enter string: ");
        scanf("%s", str);

        close(fd1[0]); // not reading from pipe1
        write(fd1[1], str, strlen(str) + 1);

        close(fd2[1]); // not writing to pipe2
        read(fd2[0], rev, sizeof(rev));

        printf("Reversed: %s\n", rev);

        if (strcmp(str, rev) == 0)
            printf("Palindrome\n");
        else
            printf("Not Palindrome\n");
    }
    else {
        // ----- CHILD -----

        char temp[100];

        close(fd1[1]); // not writing to pipe1
        read(fd1[0], temp, sizeof(temp));

        int len = strlen(temp);
        for (int i = 0; i < len; i++)
            rev[i] = temp[len - i - 1];
        rev[len] = '\0';

        close(fd2[0]); // not reading from pipe2
        write(fd2[1], rev, strlen(rev) + 1);
    }

    return 0;
}   


