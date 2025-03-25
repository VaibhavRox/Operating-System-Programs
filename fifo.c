#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int frames) {
    int frame[frames], index = 0, pageFaults = 0, pageHits = 0;
    
    for (int i = 0; i < frames; i++) {
        frame[i] = -1; // Initialize frames as empty
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        
        // Check if the page is already in a frame (Page Hit)
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                pageHits++;
                break;
            }
        }

        // If not found, replace using FIFO (Page Miss)
        if (!found) {
            frame[index] = pages[i]; // Replace the oldest page
            index = (index + 1) % frames; // Move to the next replacement index
            pageFaults++;
        }

        // Print current frame state
        printf("Step %d: ", i + 1);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf(" | %s\n", found ? "Hit" : "Miss");
    }

    printf("\nTotal Page Hits: %d\n", pageHits);
    printf("Total Page Misses (Page Faults): %d\n", pageFaults);
}

int main() {
    int n, frames;
    
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    int pages[n];

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    fifoPageReplacement(pages, n, frames);
    
    return 0;
}