#include<stdio.h>
#include<stdlib.h>
void FCFS(int requests[],int n,int head)
{
    int seek_time=0;
    printf("Seek Sequence:%d",head);
    for(int i=0;i<n;i++)
    {
        seek_time+=abs(requests[i]-head);
        head=requests[i];
        printf("->%d",head);
    }
    printf("Total number of moves:%d\n",seek_time);
}
void main()
{
    int n,head;
    printf("Enter number of disk requests:");
    scanf("%d",&n);
    int requests[n];
    printf("Enter request sequence:\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d",&head);
    FCFS(requests,n,head);
}