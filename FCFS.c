#include <stdio.h>
#include <string.h>
struct Process
{
    int pid;
    int burst;
    int completionTime;
    int turnaroundtime;
    int waitingtime;
};
void calculateTimes(struct Process p[],int n)
{
    int currenttime=0;
    for(int i=0;i<n;i++)
    {
        //completion time is current + burst time
        currenttime+=p[i].burst;
        p[i].completionTime=currenttime;
        //turnaround time = completion time
        p[i].turnaroundtime=p[i].completionTime;
        //waiting time=turnaround-burst
        p[i].waitingtime=p[i].turnaroundtime-p[i].burst;
    }
}
void printTable(struct Process p[],int n)
{
    printf("\nPID\tBurstTime\tCompletionTime\tTurnaroundTime\tWaitingTime\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].burst,p[i].completionTime,p[i].turnaroundtime,p[i].waitingtime);
    }
}
void printGantt(struct Process p[],int n)
{
    printf("\nGantt Chart:\n");
    printf(" ");
    //top border
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<p[i].burst;j++)
        {printf("-");}
        printf(" ");
    }
    printf("\n|");
    //Process IDs appear in middle
    for (int i = 0; i < n; i++) {
        int spaces = p[i].burst - 2; // Remaining spaces for padding
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
    //bottom border
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<p[i].burst;j++)
        {printf("-");}
        printf(" ");
    }
    //Time values
    printf("\n0");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<p[i].burst;j++)
        {printf(" ");}
        printf("%d",p[i].completionTime);
    }
    printf("\n");
}
void main()
{
    printf("FCFS SCHEDULING NON PREEMPTIVE");
    int n;
    printf("Enter no of process:");
    scanf("%d",&n);
    struct Process p[n];
    printf("Enter Burst Times for each process:\n");
    for(int i=0;i<n;i++)
    {
        p[i].pid=i+1;
        printf("Process %d:",i+1);
        scanf("%d",&p[i].burst);
    }
    calculateTimes(p,n);
    printTable(p,n);
    printGantt(p,n);
}