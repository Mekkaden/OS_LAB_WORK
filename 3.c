#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
    time_t now;


    printf("Current system time: %s", ctime(&now));

    sleep(60);

    return 0;
}