#include <stdio.h>

struct Process {
    int pid;           // Process ID
    int burstTime;     // Burst Time
    int completionTime; // Completion Time
    int turnAroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
};

void sortByBurstTime(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].burstTime > p[j + 1].burstTime) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(struct Process p[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        // Completion Time is current time + burst time
        currentTime += p[i].burstTime;
        p[i].completionTime = currentTime;

        // Turnaround Time = Completion Time
        p[i].turnAroundTime = p[i].completionTime;

        // Waiting Time = Turnaround Time - Burst Time
        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
    }
}

void printTable(struct Process p[], int n) {
    printf("\nPID\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burstTime,
               p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
    }
}

void printGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n");
    printf(" ");

    // Top border
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].burstTime; j++) {
            printf("-");
        }
        printf(" ");
    }
    printf("\n|");

    // Process IDs
     for (int i = 0; i < n; i++) {
        int spaces = p[i].burstTime - 2; // Remaining spaces for padding
        int leftSpaces = spaces / 2;
        int rightSpaces = spaces - leftSpaces;

        for (int j = 0; j < leftSpaces; j++) {
            printf(" ");
        }
        printf("P%d", p[i].pid);
        for (int j = 0; j < rightSpaces; j++) {
            printf(" ");
        }
        printf("|");
    }
    printf("\n ");

    // Bottom border
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].burstTime; j++) {
            printf("-");
        }
        printf(" ");
    }

    // Time values
    printf("\n0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].burstTime; j++) {
            printf(" ");
        }
        printf("%d", p[i].completionTime);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    printf("Enter the burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d", &p[i].burstTime);
    }

    // Sort processes by burst time
    sortByBurstTime(p, n);

    // Calculate times
    calculateTimes(p, n);

    // Print the table
    printTable(p, n);

    // Print the Gantt chart
    printGanttChart(p, n);

    return 0;
}
