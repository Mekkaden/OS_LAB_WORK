#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void display(int frame[], int f) {
    for(int i = 0; i < f; i++) {
        if(frame[i] == -1) printf("- ");
        else printf("%d ", frame[i]);
    }
}

// 1. FIFO: Replace the oldest page using a circular pointer
void FIFO(int ref[], int n, int f) {
    int frame[10], ptr = 0, fault = 0;
    for(int i = 0; i < f; i++) frame[i] = -1;

    printf("\n--- FIFO ---\nPage\tFrames\t\tStatus\n");
    for(int i = 0; i < n; i++) {
        int hit = 0;
        for(int j = 0; j < f; j++) {
            if(frame[j] == ref[i]) { hit = 1; break; }
        }

        printf("%d\t", ref[i]);
        if(hit == 0) {
            frame[ptr] = ref[i];
            ptr = (ptr + 1) % f; // Circular queue math
            fault++;
            display(frame, f);
            printf("\tFault\n");
        } else {
            display(frame, f);
            printf("\tHit\n");
        }
    }
    printf("Total Faults = %d\n", fault);
}

// 2. LRU: Replace the page that hasn't been used in the longest time
void LRU(int ref[], int n, int f) {
    int frame[10], time[10], clock = 0, fault = 0;
    for(int i = 0; i < f; i++) { frame[i] = -1; time[i] = 0; }

    printf("\n--- LRU ---\nPage\tFrames\t\tStatus\n");
    for(int i = 0; i < n; i++) {
        int hit = 0, pos = -1;
        for(int j = 0; j < f; j++) {
            if(frame[j] == ref[i]) { hit = 1; pos = j; break; }
        }

        printf("%d\t", ref[i]);
        if(hit == 1) {
            time[pos] = ++clock; 
            display(frame, f);
            printf("\tHit\n");
        } else {
            int min = 0;
            for(int j = 1; j < f; j++) {
                if(time[j] < time[min]) min = j;
            }
            frame[min] = ref[i];
            time[min] = ++clock; 
            fault++;
            display(frame, f);
            printf("\tFault\n");
        }
    }
    printf("Total Faults = %d\n", fault);
}

// 3. OPTIMAL: Replace the page that won't be used for the longest time in the future
void OPTIMAL(int ref[], int n, int f) {
    int frame[10], fault = 0;
    for(int i = 0; i < f; i++) frame[i] = -1;

    printf("\n--- OPTIMAL ---\nPage\tFrames\t\tStatus\n");
    for(int i = 0; i < n; i++) {
        int hit = 0;
        for(int j = 0; j < f; j++) {
            if(frame[j] == ref[i]) { hit = 1; break; }
        }

        printf("%d\t", ref[i]);
        if(hit == 1) {
            display(frame, f);
            printf("\tHit\n");
        } else {
            int pos = -1, farthest = -1;
            for(int j = 0; j < f; j++) {
                if(frame[j] == -1) { pos = j; break; } 
                
                int k;
                for(k = i + 1; k < n; k++) {
                    if(frame[j] == ref[k]) break;
                }
                
                if(k == n) { pos = j; break; }
                
                if(k > farthest) { farthest = k; pos = j; }
            }
            frame[pos] = ref[i];
            fault++;
            display(frame, f);
            printf("\tFault\n");
        }
    }
    printf("Total Faults = %d\n", fault);
}

int main(void) {
    int n, f;
    
    printf("Enter number of pages (length of reference string): ");
    if(scanf("%d", &n) != 1) return 1;
    
    printf("Enter number of frames: ");
    scanf("%d", &f);

    int ref[n];
    
    // ==========================================================
    srand(time(NULL));
    
    printf("\nGenerated Reference String: ");
    for(int i = 0; i < n; i++) {
        ref[i] = rand() % 10; // Random pages from 0 to 9
        printf("%d ", ref[i]);
    }
    printf("\n");
    // ==========================================================

    // Call the bad boys
    FIFO(ref, n, f);
    LRU(ref, n, f);
    OPTIMAL(ref, n, f);

    return 0;
}