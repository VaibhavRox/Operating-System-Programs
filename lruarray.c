#include <stdio.h>

void lru(int pages[], int n, int frames) {
    int frame[frames], recent[frames], pageFault = 0, pageHit = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;   // Initialize all frames as empty (-1)
        recent[i] = -1;  // Track recent usage (initialized to -1)
    }

    for (int i = 0; i < n; i++) {
        int found = 0, leastUsedIndex = 0;

        // Check if the page is already in a frame (Page Hit)
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                pageHit++;
                recent[j] = i;  // Update last used time
                break;
            }
        }

        if (!found) {  // Page Fault occurs
            int replaceIndex = 0;

            // Find the Least Recently Used (LRU) page
            for (int j = 1; j < frames; j++) {
                if (recent[j] < recent[replaceIndex]) {
                    replaceIndex = j;
                }
            }

            frame[replaceIndex] = pages[i]; // Replace the LRU page
            recent[replaceIndex] = i; // Update recent usage
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

    lru(pages, n, frames);

    return 0;
}