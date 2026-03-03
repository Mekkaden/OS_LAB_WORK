#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

double mean = 0.0, median = 0.0, stddev = 0.0, least = 0.0;
int *numbers;
int count;

void *compute_mean(void *arg) {
    double sum = 0;
    for (int i = 0; i < count; i++)
        sum += numbers[i];
    mean = sum / count;
    pthread_exit(NULL);
}

void *compute_median(void *arg) {
    int *temp = malloc(count * sizeof(int));

    // Copy original array
    for (int i = 0; i < count; i++)
        temp[i] = numbers[i];

    // Bubble Sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    // Median logic
    if (count % 2 == 0)
        median = (temp[count/2 - 1] + temp[count/2]) / 2.0;
    else
        median = temp[count/2];

    free(temp);
    pthread_exit(NULL);
}

void *compute_stddev(void *arg) {
    double sum = 0, local_mean = 0;

    for (int i = 0; i < count; i++)
        local_mean += numbers[i];

    local_mean /= count;

    for (int i = 0; i < count; i++)
        sum += pow(numbers[i] - local_mean, 2); //(xi - meu)^ 2

    stddev = sqrt(sum / count); // x-u / n
    pthread_exit(NULL);
}

void *compute_min(void *arg) {
    int min = numbers[0];

    for (int i = 1; i < count; i++)
        if (numbers[i] < min)
            min = numbers[i];

    least = min;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <list of integers>\n", argv[0]);
        return 1;
    }

    count = argc - 1;
    numbers = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++)
        numbers[i] = atoi(argv[i + 1]);

    pthread_t t1, t2, t3, t4;

    pthread_create(&t1, NULL, compute_mean, NULL);
    pthread_create(&t2, NULL, compute_median, NULL);
    pthread_create(&t3, NULL, compute_stddev, NULL);
    pthread_create(&t4, NULL, compute_min, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    printf("Mean   = %.2f\n", mean);
    printf("Median = %.2f\n", median);
    printf("SD     = %.2f\n", stddev);
    printf("Least  = %.2f\n", least);

    
    return 0;
}