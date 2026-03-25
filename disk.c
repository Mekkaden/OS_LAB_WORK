#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX 10
#define DISK_SIZE 5000

// Function to generate random requests
void generate_requests(int req[]) {
    for(int i = 0; i < MAX; i++) {
        req[i] = rand() % DISK_SIZE;
    }
}

// Print array
void print_requests(int req[]) {
    for(int i = 0; i < MAX; i++) {
        printf("%d ", req[i]);
    }
    printf("\n");
}

//////////////////// SSTF ////////////////////
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

        visited[index] = 1;
        total += abs(head - req[index]);
        head = req[index];

        printf("-> %d ", head);
    }

    printf("\nTotal Head Movement (SSTF): %d\n", total);
}

//////////////////// LOOK ////////////////////
void LOOK(int req[], int head) {
    int temp[MAX];
    for(int i = 0; i < MAX; i++) temp[i] = req[i];

    // sort
    for(int i = 0; i < MAX-1; i++) {
        for(int j = i+1; j < MAX; j++) {
            if(temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int total = 0, i;
    printf("\nLOOK Order: %d ", head);

    // move right
    for(i = 0; i < MAX; i++) {
        if(temp[i] >= head) {
            total += abs(head - temp[i]);
            head = temp[i];
            printf("-> %d ", head);
        }
    }

    // move left
    for(i = MAX-1; i >= 0; i--) {
        if(temp[i] < head) {
            total += abs(head - temp[i]);
            head = temp[i];
            printf("-> %d ", head);
        }
    }

    printf("\nTotal Head Movement (LOOK): %d\n", total);
}

//////////////////// CSCAN ////////////////////
void CSCAN(int req[], int head) {
    int temp[MAX];
    int start = head;
    for(int i = 0; i < MAX; i++) temp[i] = req[i];

    // sort
    for(int i = 0; i < MAX-1; i++) {
        for(int j = i+1; j < MAX; j++) {
            if(temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int total = 0, i;
    printf("\nCSCAN Order: %d ", head);

    // move right
    for(i = 0; i < MAX; i++) {
        if(temp[i] >= head) {
            total += abs(head - temp[i]);
            head = temp[i];
            printf("-> %d ", head);
        }
    }

    // go to end (4999)
    total += abs(head - (DISK_SIZE - 1));
    head = DISK_SIZE - 1;

    // jump to 0
    total += abs(head - 0);
    head = 0;

    printf("-> 4999 -> 0 ");

    // service remaining
// after jump to 0
for(i = 0; i < MAX; i++) {
    if(temp[i] < start) {
        total += abs(head - temp[i]);
        head = temp[i];
        printf("-> %d ", head);
    }
}

    printf("\nTotal Head Movement (CSCAN): %d\n", total);
}

//////////////////// FCFS ////////////////////
void FCFS(int req[], int head) {
    int total = 0;

    printf("\nFCFS Order: %d ", head);

    for(int i = 0; i < MAX; i++) {
        total += abs(head - req[i]);
        head = req[i];
        printf("-> %d ", head);
    }

    printf("\nTotal Head Movement (FCFS): %d\n", total);
}





//////////////////// SCAN ////////////////////
void SCAN(int req[], int head) {
    int temp[MAX];
    for(int i = 0; i < MAX; i++) temp[i] = req[i];

    // sort
    for(int i = 0; i < MAX-1; i++) {
        for(int j = i+1; j < MAX; j++) {
            if(temp[i] > temp[j]) {
                int t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    int total = 0;
    printf("\nSCAN Order: %d ", head);

    // move right
    for(int i = 0; i < MAX; i++) {
        if(temp[i] >= head) {
            total += abs(head - temp[i]);
            head = temp[i];
            printf("-> %d ", head);
        }
    }

    // go to end
    total += abs(head - (DISK_SIZE - 1));
    head = DISK_SIZE - 1;
    printf("-> %d ", head);

    // move left
    for(int i = MAX-1; i >= 0; i--) {
        if(temp[i] < head) {
            total += abs(head - temp[i]);
            head = temp[i];
            printf("-> %d ", head);
        }
    }

    printf("\nTotal Head Movement (SCAN): %d\n", total);
}
//////////////////// MAIN ////////////////////
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

    srand(time(0));
    generate_requests(req);

    printf("Initial Head Position: %d\n", head);
    printf("Request Queue: ");
    print_requests(req);

    SSTF(req, head);
    LOOK(req, head);
    CSCAN(req, head);

    return 0;
    }