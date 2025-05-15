#include <stdio.h>

int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[100], frames[10], time[10];
    int n_pages, n_frames, i, j, pos, page_faults = 0, counter = 0, found;

    printf("Enter the number of pages: ");
    scanf("%d", &n_pages);

    printf("Enter the page reference string:\n");
    for (i = 0; i < n_pages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &n_frames);

    for (i = 0; i < n_frames; i++) {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\n");

    for (i = 0; i < n_pages; i++) {
        found = 0;

        for (j = 0; j < n_frames; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if (!found) {
            int empty_found = 0;
            for (j = 0; j < n_frames; j++) {
                if (frames[j] == -1) {
                    counter++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    page_faults++;
                    empty_found = 1;
                    break;
                }
            }

            if (!empty_found) {
                pos = findLRU(time, n_frames);
                counter++;
                frames[pos] = pages[i];
                time[pos] = counter;
                page_faults++;
            }

            printf("%d\t", pages[i]);
            for (j = 0; j < n_frames; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        } else {
            printf("%d\tNo Page Fault\n", pages[i]);
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}
