#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// ---------- STEP 1: Declare global variables ----------
double mean = 0.0, median = 0.0, stddev = 0.0, least = 0.0;
int *numbers; //bcs we creating array by mallocing
int count;


// ---------- STEP 2: Thread function to compute Mean ----------
void *compute_mean(void *arg) {

    double sum = 0;

    // Step 2.1: Calculate sum of all numbers
    for (int i = 0; i < count; i++)
        sum += numbers[i];

    // Step 2.2: Compute mean
    mean = sum / count;

    pthread_exit(NULL);
}


// ---------- STEP 3: Thread function to compute Median ----------
void *compute_median(void *arg) {

    // Step 3.1: Allocate temporary array
    int *temp = malloc(count * sizeof(int));

    // Step 3.2: Copy original numbers into temp array
    for (int i = 0; i < count; i++)
        temp[i] = numbers[i];

    // Step 3.3: Sort numbers using Bubble Sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            if (temp[j] > temp[j + 1]) {
                int t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }

        }
    }

    // Step 3.4: Compute median
    if (count % 2 == 0)
        median = (temp[count/2 - 1] + temp[count/2]) / 2.0;
    else
        median = temp[count/2];

    // Step 3.5: Free temporary memory
    free(temp);

    pthread_exit(NULL);
}


// ---------- STEP 4: Thread function to compute Standard Deviation ----------
void *compute_stddev(void *arg) {

    double sum = 0, local_mean = 0;

    // Step 4.1: Calculate mean
    for (int i = 0; i < count; i++)
        local_mean += numbers[i];

    local_mean /= count;

    // Step 4.2: Calculate variance part (xi - mean)^2
    for (int i = 0; i < count; i++)
        sum += pow(numbers[i] - local_mean, 2);

    // Step 4.3: Compute standard deviation
    stddev = sqrt(sum / count);

    pthread_exit(NULL);
}


// ---------- STEP 5: Thread function to compute Minimum ----------
void *compute_min(void *arg) {

    int min = numbers[0];

    // Step 5.1: Find smallest number
    for (int i = 1; i < count; i++)
        if (numbers[i] < min)
            min = numbers[i];

    // Step 5.2: Store result
    least = min;

    pthread_exit(NULL);
}


// ---------- STEP 6: Main Function ----------
int main(int argc, char *argv[]) {

    // Step 6.1: Check if numbers are provided
    if (argc < 2) {
        printf("Usage: %s <list of integers>\n", argv[0]);
        return 1;
    }

    // Step 6.2: Determine number of inputs
    count = argc - 1;

    // Step 6.3: Allocate memory for numbers
    numbers = malloc(count * sizeof(int));

    // Step 6.4: Convert command line arguments to integers
    for (int i = 0; i < count; i++)
        numbers[i] = atoi(argv[i + 1]);

    // Step 6.5: Declare thread IDs
    pthread_t t1, t2, t3, t4;

    // Step 6.6: Create threads for each statistical calculation
    pthread_create(&t1, NULL, compute_mean, NULL);
    pthread_create(&t2, NULL, compute_median, NULL);
    pthread_create(&t3, NULL, compute_stddev, NULL);
    pthread_create(&t4, NULL, compute_min, NULL);

    // Step 6.7: Wait for all threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    // Step 6.8: Display results
    printf("Mean   = %.2f\n", mean);
    printf("Median = %.2f\n", median);
    printf("SD     = %.2f\n", stddev);
    printf("Least  = %.2f\n", least);

    return 0;
}