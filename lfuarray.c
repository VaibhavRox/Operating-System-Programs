#include <stdio.h>

void lfu(int pages[], int n, int frames) {
    int frame[frames], freq[frames], pageFault = 0, pageHit = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;   // Initialize frames as empty (-1)
        freq[i] = 0;     // Initialize frequency to 0
    }

    for (int i = 0; i < n; i++) {
        int found = 0, leastUsedIndex = 0;

        // Check if the page is already in a frame (Page Hit)
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                pageHit++;
                freq[j]++;  // Increase frequency of usage
                break;
            }
        }

        if (!found) {  // Page Fault occurs
            int replaceIndex = 0;

            // Find the Least Frequently Used (LFU) page
            for (int j = 1; j < frames; j++) {
                if (freq[j] < freq[replaceIndex]) {
                    replaceIndex = j;
                }
            }

            frame[replaceIndex] = pages[i]; // Replace LFU page
            freq[replaceIndex] = 1;  // Reset frequency for new page
            pageFault++;
        }

        // Print frame status
        printf("Step %d: ", i + 1);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("%s\n", found ? "Hit" : "Miss");
    }

    printf("\nTotal Page Hits: %d\n", pageHit);
    printf("Total Page Faults: %d\n", pageFault);
}

int main() {
    int n, frames;

    printf("Enter the number of pages: ");
    scanf("%d", &n);
    int pages[n];

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) 
        scanf("%d", &pages[i]);

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    lfu(pages, n, frames);

    return 0;
}