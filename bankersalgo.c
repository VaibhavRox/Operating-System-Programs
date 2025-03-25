#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES], work[MAX_RESOURCES], finish[MAX_PROCESSES];
int n, m; // Number of processes and resources

// Function to check if the system is in a safe state
int isSafe() {
    int safeSequence[MAX_PROCESSES], count = 0;
    
    // Initialize Work and Finish
    for (int i = 0; i < m; i++)
        work[i] = available[i];

    for (int i = 0; i < n; i++)
        finish[i] = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int canAllocate = 1;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = 0;
                        break;
                    }
                }

                if (canAllocate) {
                    // Allocate resources
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("System is in an *UNSAFE* state! Deadlock may occur.\n");
            return 0;
        }
    }

    printf("System is in a *SAFE* state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");

    return 1;
}

// Function to process a new resource request
void requestResources(int process, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process P%d has requested more than its max need!\n", process);
            return;
        }
        if (request[i] > available[i]) {
            printf("Process P%d must wait: Not enough available resources.\n", process);
            return;
        }
    }

    // Tentatively allocate resources
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system remains in a safe state
    if (!isSafe()) {
        printf("Request by P%d cannot be granted to avoid deadlock.\n", process);
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    } else {
        printf("Request by P%d has been granted successfully.\n", process);
    }
}

// Main function
int main() {
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    // Calculate Need Matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Display matrices
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    // Check initial system state
    isSafe();

    // Handling a resource request
    int process;
    int request[MAX_RESOURCES];

    printf("\nEnter process number requesting resources: ");
    scanf("%d", &process);

    printf("Enter requested resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    requestResources(process, request);

    return 0;
}