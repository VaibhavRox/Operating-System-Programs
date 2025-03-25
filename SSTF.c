#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void SSTF(int request[],int n,int head)
{
    int seek_time=0,completed=0;
    int visited[n];
    for(int i=0;i<n;i++) visited[i]=0;
    printf("Seek Sequence:%d",head);
    while(completed<n)
    {
        int min_dist=999,index=-1;
        for(int i=0;i<n;i++)
        {
            if(!visited[i])
            {
                int distance=abs(request[i]-head);
                if(distance<min_dist)
                {
                    min_dist=distance;
                    index=i;
                }
            }
        }
        seek_time+=min_dist;
        head=request[index];
        visited[index]=1;
        completed++;
        printf("->%d",head);
    }
    printf("\nTotal seek time:%d\n",seek_time);
}
void main()
{
    int n,head;
    printf("Enter the number of request:");
    scanf("%d",&n);
    int request[n];
    printf("Enter request sequence:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&request[i]);
    }
    printf("Enter the head position:");
    scanf("%d",&head);
    SSTF(request,n,head);
}