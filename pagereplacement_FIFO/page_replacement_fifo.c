#include <stdio.h>

int main() {
    int pages[100], frames[10];
    int n_pages, n_frames, i, j, k, page_faults = 0, index = 0, found;

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
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % n_frames;
            page_faults++;

            printf("%d\t", pages[i]);
            for (k = 0; k < n_frames; k++) {
                if (frames[k] != -1)
                    printf("%d ", frames[k]);
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
