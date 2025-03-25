#include <stdio.h>
void firstFit(int blocksize[], int m, int processSize[],int n)
{
    int allocation[n];
    for(int i=0;i<n;i++)
    {   allocation[i]=-1;}      //initialize all processes as unallocated

    for(int i=0;i<n;i++)
    {   
        for(int j=0;j<m;j++)
            {
                if(blocksize[j]>=processSize[i])
                {
                    allocation[i]=j;
                    blocksize[j]-=processSize[i];
                    break;
                }
            }
    }
    printf("First Fit:\n");
    printf("Process no:\tProcess Size\tBlock no:\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t",i+1,processSize[i]);
        if(allocation[i]!=-1)
            {printf("%d\n",allocation[i]+1);}
        else
            {printf("Not Allocated");}
    }
}
void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++) {
        int bestIdx = -1;
        for(int j = 0; j < m; j++) {
            if(blockSize[j] >= processSize[i]) {
                if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
        if(bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for(int i = 0; i < n; i++)
        allocation[i] = -1;

    for(int i = 0; i < n; i++) {
        int worstIdx = -1;
        for(int j = 0; j < m; j++) {
            if(blockSize[j] >= processSize[i]) {
                if(worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }
        if(worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter the size of each memory block:\n");
    for(int i = 0; i < m; i++) {
        printf("Block %d: ", i+1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter the size of each process:\n");
    for(int i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d", &processSize[i]);
    }

    int blockCopy1[m], blockCopy2[m], blockCopy3[m];

    for(int i = 0; i < m; i++) {
        blockCopy1[i] = blockSize[i];
        blockCopy2[i] = blockSize[i];
        blockCopy3[i] = blockSize[i];
    }

    firstFit(blockCopy1, m, processSize, n);
    bestFit(blockCopy2, m, processSize, n);
    worstFit(blockCopy3, m, processSize, n);

    return 0;
}
