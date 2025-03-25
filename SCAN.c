#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void SCAN(int request[],int n,int head,int disksize)
{
    for(int i=0;i<n-1;i++)
    {for(int j=0;j<n-i-1;j++)
        if(request[j]>request[j+1])
        {
            int temp=request[j];
            request[j]=request[j+1];
            request[j+1]=temp;
        }
    }
    int seek_time=0,direction;
    printf("Enter the direction of movement(0->left,1->right):");
    scanf("%d",&direction);
    printf("Seek Sequence:%d",head);
    if(direction==1)    //right
    {
        for(int i=0;i<n;i++)
        {
            int counter=0;
            if(request[i]>=head)
            {
                for(int j=i;j<n;j++)
                {
                    seek_time+=abs(request[j]-head);
                    head=request[j];
                    counter++;
                    printf("->%d",head);
                }
                if(counter==n)break; //all requests done
                if(head!=disksize-1) //to reach the end
                {
                    seek_time+=abs((disksize-1)-head);
                    head=disksize-1;
                }
                for(int j=i-1;j>=0;j--)
                {
                    seek_time+=abs(request[j]-head);
                    head=request[j];
                    printf("->%d",head);
                }
                break;
            }
        }
    }
    else        //going left
    {
        for(int i=n-1;i>=0;i--)
        {
            int counter=0;
            if(request[i]<=head)
            {
                for(int j=i;j>=0;j--)
                {
                    seek_time+=abs(request[j]-head);
                    head=request[j];
                    counter++;
                    printf("->%d",head);
                }
                if(counter==n)break;
                if(head!=0) //reach left end
                {
                    seek_time+=head;
                    head=0;
                }
                for(int j=i+1;j<n;j++)
                {
                    seek_time+=abs(request[j]-head);
                    head=request[j];
                    printf("->%d",head);
                }
                break;
            }
        }
    }
    printf("\nTotal seek time:%d\n",seek_time);
}
void main()
{
    int n,head,disksize;
    printf("Enter number of request:");
    scanf("%d",&n);
    int request[n];
    printf("Enter request sequence:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&request[i]);
    }
    printf("Enter the head position:");
    scanf("%d",&head);
    printf("Enter disksize:");
    scanf("%d",&disksize);
    SCAN(request,n,head,disksize);
}