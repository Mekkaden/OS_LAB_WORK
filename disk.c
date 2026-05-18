#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX 10
#define DISK_SIZE 5000

void generate_requests(int req[]) {
    for(int i = 0; i < MAX; i++) {
        req[i] = rand() % DISK_SIZE;
    }
}

void print_requests(int req[]) {
    for(int i = 0; i < MAX; i++) {
        printf("%d ", req[i]);
    }
    printf("\n");
}

void SSTF(int req[], int head) {
    int visited[MAX] = {0};
    int total = 0;

    printf("\nSSTF Order: %d ", head);

    for(int i = 0; i < MAX; i++) {
        int min = INT_MAX, index = -1;

        for(int j = 0; j < MAX; j++) {
            if(!visited[j]) {
                int dist = abs(head - req[j]);
                if(dist < min) {
                    min = dist;
                    index = j;
                }
            }
        }

        if(index == -1) break;

        visited[index] = 1;
        total += abs(head - req[index]);
        head = req[index];

        printf("-> %d ", head);
    }

    printf("\nTotal Head Movement (SSTF): %d\n", total);
}

void LOOK(int req[], int head) {
    int temp[MAX];
    int start = head;

    for(int i = 0; i < MAX; i++)
        temp[i] = req[i];

    for(int i = 0; i < MAX - 1; i++) {
        for(int j = i + 1; j < MAX; j++) {
            if(temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int total = 0;
    printf("\nLOOK Order: %d ", head);

    for(int i = 0; i < MAX; i++) {
        if(temp[i] >= start) {
            total += abs(head - temp[i]);
            head = temp[i];
            printf("-> %d ", head);
        }
    }

    for(int i = MAX - 1; i >= 0; i--) {
        if(temp[i] < start) {
            total += abs(head - temp[i]);
            head = temp[i];
            printf("-> %d ", head);
        }
    }

    printf("\nTotal Head Movement (LOOK): %d\n", total);
}

void CSCAN(int req[], int head) {
    int temp[MAX];
    int start = head;

    for(int i = 0; i < MAX; i++)
        temp[i] = req[i];

    for(int i = 0; i < MAX - 1; i++) {
        for(int j = i + 1; j < MAX; j++) {
            if(temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int total = 0;
    printf("\nCSCAN Order: %d ", head);

    for(int i = 0; i < MAX; i++) {
        if(temp[i] >= head) {
            total += abs(head - temp[i]);
            head = temp[i];
            printf("-> %d ", head);
        }
    }

    total += abs(head - (DISK_SIZE - 1));
    head = DISK_SIZE - 1;

    total += abs(head - 0);
    head = 0;

    printf("-> %d -> %d ", DISK_SIZE - 1, 0);

    for(int i = 0; i < MAX; i++) {
        if(temp[i] < start) {
            total += abs(head - temp[i]);
            head = temp[i];
            printf("-> %d ", head);
        }
    }

    printf("\nTotal Head Movement (CSCAN): %d\n", total);
}

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: %s <initial_head_position>\n", argv[0]);
        return 1;
    }

    int head = atoi(argv[1]);

    if(head < 0 || head >= DISK_SIZE) {
        printf("Invalid head position! Must be between 0 and 4999\n");
        return 1;
    }

    int req[MAX];

    srand(time(NULL));
    generate_requests(req);

    printf("Initial Head Position: %d\n", head);
    printf("Request Queue: ");
    print_requests(req);

    SSTF(req, head);
    LOOK(req, head);
    CSCAN(req, head);

    return 0;
}