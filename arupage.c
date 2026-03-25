#include <stdio.h>

int main() {
    int ref[20], frame[10], time[10];
    int n, f, i, j, faults = 0, counter = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // initialize
    for(i = 0; i < f; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    for(i = 0; i < n; i++) {
        int found = 0;

        // check hit
        for(j = 0; j < f; j++) {
            if(frame[j] == ref[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        // page fault
        if(!found) {
            int min = 9999, pos = 0;

            for(j = 0; j < f; j++) {
                if(time[j] < min) {
                    min = time[j];
                    pos = j;
                }
            }

            frame[pos] = ref[i];
            counter++;
            time[pos] = counter;
            faults++;
        }
    }

    printf("Total Page Faults = %d\n", faults);
    return 0;
}