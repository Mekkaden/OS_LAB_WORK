#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<math.h>

int main() {
    int a, b, c;
    int fd[2];

    printf("Enter values of a b and c: ");
    scanf("%d %d %d", &a, &b, &c);

    pipe(fd);

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
    }
    else if (pid == 0) {   // Child
        close(fd[0]);      
        int ac = 4 * a * c;
        write(fd[1], &ac, sizeof(ac));
        close(fd[1]);
    }
    else {   // Parent
        close(fd[1]);
        int ac;
        read(fd[0], &ac, sizeof(ac));
        close(fd[0]);

        int bsq = b * b;
        int disc = bsq - ac;

        if (disc < 0) {
            printf("Imaginary roots\n");
        } else {
            printf("Square root of discriminant is %.2f\n", sqrt(disc));
        }

        wait(NULL);
    }

    return 0;
}