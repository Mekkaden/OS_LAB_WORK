#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. FCFS: Process requests exactly as they arrive (Unsorted)
void FCFS(int req[], int n, int head) {
    int total = 0;
    
    printf("\nFCFS Order: %d", head);
    for(int i = 0; i < n; i++) {
        total += abs(head - req[i]);
        head = req[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Head Movement (FCFS): %d\n", total);
}

// 2. SSTF: Find closest unvisited track
void SSTF(int req[], int n, int head) {
    int visited[100] = {0}, total = 0;
    
    printf("\nSSTF Order: %d", head);
    for(int i = 0; i < n; i++) {
        int min_dist = 99999, idx = -1; 
        
        for(int j = 0; j < n; j++) {
            if(!visited[j] && abs(head - req[j]) < min_dist) {
                min_dist = abs(head - req[j]);
                idx = j;
            }
        }
        visited[idx] = 1;
        total += min_dist;
        head = req[idx];
        printf(" -> %d", head);
    }
    printf("\nTotal Head Movement (SSTF): %d\n", total);
}

// 3. SCAN: Go right, hit the absolute boundary wall, then reverse left
void SCAN(int req[], int n, int head, int disk_size) {
    int total = 0, start = head;
    
    printf("\nSCAN Order: %d", head);
    // Move Right
    for(int i = 0; i < n; i++) {
        if(req[i] >= start) {
            total += abs(head - req[i]);
            head = req[i];
            printf(" -> %d", head);
        }
    }
    
    // Force physical head to hit the absolute end boundary wall
    total += abs(head - (disk_size - 1));
    head = disk_size - 1;
    printf(" -> %d", head);
    
    // Move Left
    for(int i = n - 1; i >= 0; i--) {
        if(req[i] < start) {
            total += abs(head - req[i]);
            head = req[i];
            printf(" -> %d", head);
        }
    }
    printf("\nTotal Head Movement (SCAN): %d\n", total);
}

// 4. LOOK: Go right to highest request, then reverse left immediately
void LOOK(int req[], int n, int head) {
    int total = 0, start = head;
    
    printf("\nLOOK Order: %d", head);
    // Move Right
    for(int i = 0; i < n; i++) {
        if(req[i] >= start) {
            total += abs(head - req[i]);
            head = req[i];
            printf(" -> %d", head);
        }
    }
    // Move Left
    for(int i = n - 1; i >= 0; i--) {
        if(req[i] < start) {
            total += abs(head - req[i]);
            head = req[i];
            printf(" -> %d", head);
        }
    }
    printf("\nTotal Head Movement (LOOK): %d\n", total);
}

// 5. CSCAN: Go right to disk end, wrap to 0, continue right
void CSCAN(int req[], int n, int head, int disk_size) {
    int total = 0, start = head;
    
    printf("\nCSCAN Order: %d", head);
    // Move Right to the largest request
    for(int i = 0; i < n; i++) {
        if(req[i] >= start) {
            total += abs(head - req[i]);
            head = req[i];
            printf(" -> %d", head);
        }
    }
    // Force jump to absolute disk edge, then wrap instantly to 0
    total += abs(head - (disk_size - 1));
    total += (disk_size - 1); 
    printf(" -> %d -> 0", disk_size - 1);
    head = 0;
    
    // Continue moving Right from 0
    for(int i = 0; i < n; i++) {
        if(req[i] < start) {
            total += abs(head - req[i]);
            head = req[i];
            printf(" -> %d", head);
        }
    }
    printf("\nTotal Head Movement (CSCAN): %d\n", total);
}

// 6. CLOOK: Go right to highest request, wrap straight to lowest request, continue right
void CLOOK(int req[], int n, int head) {
    int total = 0, start = head;
    
    printf("\nCLOOK Order: %d", head);
    // Move Right to the largest request
    for(int i = 0; i < n; i++) {
        if(req[i] >= start) {
            total += abs(head - req[i]);
            head = req[i];
            printf(" -> %d", head);
        }
    }
    // Wrap around directly to the lowest request and continue Right
    for(int i = 0; i < n; i++) {
        if(req[i] < start) {
            total += abs(head - req[i]);
            head = req[i];
            printf(" -> %d", head);
        }
    }
    printf("\nTotal Head Movement (CLOOK): %d\n", total);
}

int main(void) {
    int n, head, disk_size = 5000; 
    
    printf("Enter number of requests: ");
    if(scanf("%d", &n) != 1) return 1;
    
    printf("Enter initial head position: ");
    scanf("%d", &head);

    // --- CLEAN INLINE RAND GENERATION ---
    srand(time(NULL)); 

    int req[n];
    printf("Generated Request Queue: ");
    for(int i = 0; i < n; i++) {
        req[i] = rand() % disk_size; 
        printf("%d ", req[i]); 
    }
    printf("\n");

    // 1. Run FCFS FIRST while the array is still completely unsorted
    FCFS(req, n, head);

    // --- THE MAGIC TRICK: Sort the array ONCE right here ---
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(req[j] > req[j+1]) {
                int temp = req[j];
                req[j] = req[j+1];
                req[j+1] = temp;
            }
        }
    }

    // 2. Run the remaining sorted-dependent bad boys
    SSTF(req, n, head);
    SCAN(req, n, head, disk_size);
    LOOK(req, n, head);
    CSCAN(req, n, head, disk_size);
    CLOOK(req, n, head);

    return 0;
}