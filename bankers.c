#include <stdio.h>

// --- THE HACK: Global matrices so we don't have to pass them to functions ---
int n, m;
int alloc[10][10], max[10][10], need[10][10], avail[10];

// --- THE SAFETY FUNCTION ---
// Returns 1 if safe, 0 if unsafe.
int checkSafe() {
    int work[10], finish[10] = {0}, safeSeq[10];
    int count = 0;

    for(int i = 0; i < m; i++) 
        work[i] = avail[i];

    while(count < n) {
        int found = 0;
        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int j;
                // Check if need <= work
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) 
                        break;
                }

                // If process can be executed
                if(j == m) {
                    for(int k = 0; k < m; k++) 
                        work[k] += alloc[i][k]; // Free resources
                    
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        // If we looped through all processes and couldn't execute any, it's unsafe
        if(found == 0) {
            printf("\nSystem is NOT in a safe state.\n");
            return 0; 
        }
    }

    printf("\nSystem is in SAFE state.\nSafe Sequence: ");
    for(int i = 0; i < n; i++) 
        printf("P%d ", safeSeq[i]);
    printf("\n");
    
    return 1; // Safe
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Optimization: Calculate NEED matrix while taking MAX input
    printf("Enter Max matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j]; 
        }
    }

    printf("Enter Available resources:\n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // 1. Initial Safety Check
    printf("\n--- Initial System Check ---");
    checkSafe();

    // ==========================================
    // RESOURCE REQUEST ALGORITHM
    // ==========================================
    int pid, req[10];
    printf("\nEnter process no. making request: ");
    scanf("%d", &pid);

    printf("Enter request vector:\n");
    for(int j = 0; j < m; j++) {
        scanf("%d", &req[j]);
    }

    // Step 1: Check if Request <= Need and Request <= Available
    for(int j = 0; j < m; j++) {
        if(req[j] > need[pid][j]) {
            printf("Error: Request exceeds maximum need.\n");
            return 0;
        }
        if(req[j] > avail[j]) {
            printf("Process must wait... resource not available.\n");
            return 0;
        }
    }

    // Step 2: Pretend to allocate resources
    for(int j = 0; j < m; j++) {
        avail[j] -= req[j];
        alloc[pid][j] += req[j];
        need[pid][j] -= req[j];
    }

    // Step 3: THE MISSING RULE - Check Safety Again!
    printf("\n--- Checking Safety After Request ---");
    if(checkSafe() == 1) {
        printf("Request can be granted immediately.\n");
    } else {
        printf("Request denied to avoid deadlock. Rolling back...\n");
        // Rollback the simulated allocation
        for(int j = 0; j < m; j++) {
            avail[j] += req[j];
            alloc[pid][j] -= req[j];
            need[pid][j] += req[j];
        }
    }

    return 0;
}