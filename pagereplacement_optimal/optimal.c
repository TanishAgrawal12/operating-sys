#include <stdio.h>

int predict(int pages[], int frames[], int n_pages, int index, int n_frames) {
    int i, j, farthest = index, result = -1;
    
    for (i = 0; i < n_frames; i++) {
        int found = 0;
        for (j = index + 1; j < n_pages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    result = i;
                }
                found = 1;
                break;
            }
        }
        if (!found)
            return i;
    }

    return (result == -1) ? 0 : result;
}

int main() {
    int pages[100], frames[10];
    int n_pages, n_frames, i, j, page_faults = 0, filled = 0, found;

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
            if (filled < n_frames) {
                frames[filled++] = pages[i];
            } else {
                int pos = predict(pages, frames, n_pages, i, n_frames);
                frames[pos] = pages[i];
            }

            page_faults++;

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
