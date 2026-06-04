#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

// ─────────────────────────────────────────────
//  Utility: print memory state
// ─────────────────────────────────────────────
void printMemory(int blocks[], int n, int alloc[], int m) {
    printf("\n  %-12s %-12s %-15s\n", "Process", "Size", "Block Assigned");
    printf("  %-12s %-12s %-15s\n", "-------", "----", "--------------");
    for (int i = 0; i < m; i++) {
        if (alloc[i] != -1)
            printf("  P%-11d %-12d Block %d (size %d)\n",
                   i + 1, /* process size printed separately */ 0,
                   alloc[i] + 1, blocks[alloc[i]]);
        else
            printf("  P%-11d %-12s %s\n", i + 1, "-", "Not Allocated");
    }
}

// ─────────────────────────────────────────────
//  1. First Fit
// ─────────────────────────────────────────────
void firstFit(int blocks[], int n, int processes[], int m) {
    printf("\n╔══════════════════════════════════╗");
    printf("\n║        FIRST FIT ALGORITHM       ║");
    printf("\n╚══════════════════════════════════╝\n");

    int blockCopy[MAX_BLOCKS];
    memcpy(blockCopy, blocks, n * sizeof(int));

    int alloc[MAX_PROCESSES];
    for (int i = 0; i < m; i++) alloc[i] = -1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (blockCopy[j] >= processes[i]) {
                alloc[i] = j;
                blockCopy[j] -= processes[i];
                break;
            }
        }
    }

    printf("\n  %-12s %-12s %-15s\n", "Process", "Size (KB)", "Block Assigned");
    printf("  %-12s %-12s %-15s\n", "-------", "---------", "--------------");
    for (int i = 0; i < m; i++) {
        if (alloc[i] != -1)
            printf("  P%-11d %-12d Block %d\n", i + 1, processes[i], alloc[i] + 1);
        else
            printf("  P%-11d %-12d Not Allocated\n", i + 1, processes[i]);
    }

    printf("\n  Remaining block sizes: ");
    for (int i = 0; i < n; i++) printf("[%d] ", blockCopy[i]);
    printf("\n");
}

// ─────────────────────────────────────────────
//  2. Best Fit
// ─────────────────────────────────────────────
void bestFit(int blocks[], int n, int processes[], int m) {
    printf("\n╔══════════════════════════════════╗");
    printf("\n║        BEST FIT ALGORITHM        ║");
    printf("\n╚══════════════════════════════════╝\n");

    int blockCopy[MAX_BLOCKS];
    memcpy(blockCopy, blocks, n * sizeof(int));

    int alloc[MAX_PROCESSES];
    for (int i = 0; i < m; i++) alloc[i] = -1;

    for (int i = 0; i < m; i++) {
        int bestIdx = -1;
        for (int j = 0; j < n; j++) {
            if (blockCopy[j] >= processes[i]) {
                if (bestIdx == -1 || blockCopy[j] < blockCopy[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            alloc[i] = bestIdx;
            blockCopy[bestIdx] -= processes[i];
        }
    }

    printf("\n  %-12s %-12s %-15s\n", "Process", "Size (KB)", "Block Assigned");
    printf("  %-12s %-12s %-15s\n", "-------", "---------", "--------------");
    for (int i = 0; i < m; i++) {
        if (alloc[i] != -1)
            printf("  P%-11d %-12d Block %d\n", i + 1, processes[i], alloc[i] + 1);
        else
            printf("  P%-11d %-12d Not Allocated\n", i + 1, processes[i]);
    }

    printf("\n  Remaining block sizes: ");
    for (int i = 0; i < n; i++) printf("[%d] ", blockCopy[i]);
    printf("\n");
}

// ─────────────────────────────────────────────
//  3. Worst Fit
// ─────────────────────────────────────────────
void worstFit(int blocks[], int n, int processes[], int m) {
    printf("\n╔══════════════════════════════════╗");
    printf("\n║       WORST FIT ALGORITHM        ║");
    printf("\n╚══════════════════════════════════╝\n");

    int blockCopy[MAX_BLOCKS];
    memcpy(blockCopy, blocks, n * sizeof(int));

    int alloc[MAX_PROCESSES];
    for (int i = 0; i < m; i++) alloc[i] = -1;

    for (int i = 0; i < m; i++) {
        int worstIdx = -1;
        for (int j = 0; j < n; j++) {
            if (blockCopy[j] >= processes[i]) {
                if (worstIdx == -1 || blockCopy[j] > blockCopy[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            alloc[i] = worstIdx;
            blockCopy[worstIdx] -= processes[i];
        }
    }

    printf("\n  %-12s %-12s %-15s\n", "Process", "Size (KB)", "Block Assigned");
    printf("  %-12s %-12s %-15s\n", "-------", "---------", "--------------");
    for (int i = 0; i < m; i++) {
        if (alloc[i] != -1)
            printf("  P%-11d %-12d Block %d\n", i + 1, processes[i], alloc[i] + 1);
        else
            printf("  P%-11d %-12d Not Allocated\n", i + 1, processes[i]);
    }

    printf("\n  Remaining block sizes: ");
    for (int i = 0; i < n; i++) printf("[%d] ", blockCopy[i]);
    printf("\n");
}

// ─────────────────────────────────────────────
//  Main
// ─────────────────────────────────────────────
int main() {
    int n, m;

    printf("=== Memory Allocation Simulator ===\n");

    printf("\nEnter number of memory blocks: ");
    scanf("%d", &n);

    int blocks[MAX_BLOCKS];
    printf("Enter size of each block (in KB):\n");
    for (int i = 0; i < n; i++) {
        printf("  Block %d: ", i + 1);
        scanf("%d", &blocks[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &m);

    int processes[MAX_PROCESSES];
    printf("Enter size of each process (in KB):\n");
    for (int i = 0; i < m; i++) {
        printf("  Process %d: ", i + 1);
        scanf("%d", &processes[i]);
    }

    printf("\n┌─────────────────────────────────┐");
    printf("\n│  Memory Blocks: ");
    for (int i = 0; i < n; i++) printf("%d ", blocks[i]);
    printf("\n│  Processes:     ");
    for (int i = 0; i < m; i++) printf("%d ", processes[i]);
    printf("\n└─────────────────────────────────┘");

    firstFit(blocks, n, processes, m);
    bestFit(blocks, n, processes, m);
    worstFit(blocks, n, processes, m);

    return 0;
}