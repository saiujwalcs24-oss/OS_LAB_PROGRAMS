#include <stdio.h>
#include <string.h>

#define MAX_FRAMES 10
#define MAX_PAGES  50
#define INT_MAX_VAL 999999

// ─────────────────────────────────────────────
//  Utility
// ─────────────────────────────────────────────
int isPresent(int frames[], int n, int page) {
    for (int i = 0; i < n; i++)
        if (frames[i] == page) return 1;
    return 0;
}

void printFrames(int frames[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) printf("- ");
        else printf("%d ", frames[i]);
    }
    printf("]");
}

// ─────────────────────────────────────────────
//  1. FIFO
// ─────────────────────────────────────────────
void fifo(int pages[], int n, int f) {
  
    printf("\n---FIFO PAGE REPLACEMENT---");
    

    int frames[MAX_FRAMES];
    for (int i = 0; i < f; i++) frames[i] = -1;

    int front = 0, faults = 0, hits = 0;

    printf("\n  %-8s %-30s %-10s\n", "Page", "Frames", "Status");
    printf("  %-8s %-30s %-10s\n", "----", "------", "------");

    for (int i = 0; i < n; i++) {
        printf("  %-8d", pages[i]);
        if (isPresent(frames, f, pages[i])) {
            printFrames(frames, f);
            printf("  HIT\n");
            hits++;
        } else {
            frames[front] = pages[i];
            front = (front + 1) % f;
            printFrames(frames, f);
            printf("  PAGE FAULT\n");
            faults++;
        }
    }

    printf("\n  Total Page Faults : %d", faults);
    printf("\n  Total Page Hits   : %d", hits);
    printf("\n  Hit Ratio         : %.2f%%\n", (float)hits / n * 100);
}

// ─────────────────────────────────────────────
//  2. LRU
// ─────────────────────────────────────────────
void lru(int pages[], int n, int f) {
    
    printf("\n----LRU PAGE REPLACEMENT---");
   

    int frames[MAX_FRAMES], lastUsed[MAX_FRAMES];
    for (int i = 0; i < f; i++) { frames[i] = -1; lastUsed[i] = -1; }

    int faults = 0, hits = 0, filled = 0;

    printf("\n  %-8s %-30s %-10s\n", "Page", "Frames", "Status");
    printf("  %-8s %-30s %-10s\n", "----", "------", "------");

    for (int i = 0; i < n; i++) {
        printf("  %-8d", pages[i]);
        if (isPresent(frames, f, pages[i])) {
            for (int j = 0; j < f; j++)
                if (frames[j] == pages[i]) { lastUsed[j] = i; break; }
            printFrames(frames, f);
            printf("  HIT\n");
            hits++;
        } else {
            if (filled < f) {
                frames[filled] = pages[i];
                lastUsed[filled] = i;
                filled++;
            } else {
                int lruIdx = 0;
                for (int j = 1; j < f; j++)
                    if (lastUsed[j] < lastUsed[lruIdx]) lruIdx = j;
                frames[lruIdx] = pages[i];
                lastUsed[lruIdx] = i;
            }
            printFrames(frames, f);
            printf("  PAGE FAULT\n");
            faults++;
        }
    }

    printf("\n  Total Page Faults : %d", faults);
    printf("\n  Total Page Hits   : %d", hits);
    printf("\n  Hit Ratio         : %.2f%%\n", (float)hits / n * 100);
}

// ─────────────────────────────────────────────
//  3. Optimal
// ─────────────────────────────────────────────
int nextUse(int pages[], int n, int current, int page) {
    for (int i = current + 1; i < n; i++)
        if (pages[i] == page) return i;
    return INT_MAX_VAL;
}

void optimal(int pages[], int n, int f) {
    
    printf("\n---OPTIMAL PAGE REPLACEMENT----");
    

    int frames[MAX_FRAMES];
    for (int i = 0; i < f; i++) frames[i] = -1;

    int faults = 0, hits = 0, filled = 0;

    printf("\n  %-8s %-30s %-10s\n", "Page", "Frames", "Status");
    printf("  %-8s %-30s %-10s\n", "----", "------", "------");

    for (int i = 0; i < n; i++) {
        printf("  %-8d", pages[i]);
        if (isPresent(frames, f, pages[i])) {
            printFrames(frames, f);
            printf("  HIT\n");
            hits++;
        } else {
            if (filled < f) {
                frames[filled++] = pages[i];
            } else {
                // Find the frame whose next use is farthest
                int farthest = -1, replaceIdx = 0;
                for (int j = 0; j < f; j++) {
                    int next = nextUse(pages, n, i, frames[j]);
                    if (next > farthest) {
                        farthest = next;
                        replaceIdx = j;
                    }
                }
                frames[replaceIdx] = pages[i];
            }
            printFrames(frames, f);
            printf("  PAGE FAULT\n");
            faults++;
        }
    }

    printf("\n  Total Page Faults : %d", faults);
    printf("\n  Total Page Hits   : %d", hits);
    printf("\n  Hit Ratio         : %.2f%%\n", (float)hits / n * 100);
}


int main() {
    int n, f;

    printf("\nEnter number of frames : ");
    scanf("%d", &f);

    printf("Enter number of pages  : ");
    scanf("%d", &n);

    int pages[MAX_PAGES];
    printf("Enter page reference string:\n  ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    printf("\n  Reference String: ");
    for (int i = 0; i < n; i++) printf("%d ", pages[i]);
    printf("\n  Frames: %d\n", f);

    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);

    return 0;
}