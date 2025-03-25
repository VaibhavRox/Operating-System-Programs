#include <stdio.h>
#include <stdlib.h>
struct node{
    int page,count;
    struct node* next,*prev;
}*head;
struct node* createNode(int page)
{
    struct node* new=(struct node*)malloc(sizeof(struct node));
    new->page=page;
    new->count=1;
    new->next=new->prev=NULL;
    return new;
}
void deleteLFU()
{
    if(!head->next)return;
    struct node* top=head->next;
    struct node* temp=head->next;
    while(temp)
    {
        if(temp->count<top->count) top=temp;
        temp=temp->next;
    }
    if(top->prev)top->prev->next=top->next;
    if(top->next)top->next->prev=top->prev;
    free(temp);
}
struct node *search(int page)
{
    struct node *temp=head->next;
    while(temp)
    {
        if(temp->page==page)
            return temp; //page found
        temp=temp->next;
    }
    return NULL; //page not found
}
void LFU(int pages[],int n,int frames)
{
    int pf=0,ph=0,count=0;
    printf("Page   Frame\n");
    for(int i=0;i<n;i++)
    {
        printf("%d",pages[i]);
        struct node* existing=search(pages[i]);
        if(existing)
        {
            ph++;
            existing->count++;
            printf("Hit");
        }
        else
        {
            pf++;
            if(count==frames)
            {
                deleteLFU();count--;
            }
            struct node* new=createNode(pages[i]);
            struct node* temp=head->next;
            while(temp&&temp->next)
            {
                temp=temp->next;
            }
            if(temp)
            {
                temp->next=new;
                new->prev=temp;
            }
            else
            {
                head->next=new;
                new->prev=head;
            }
            count++;
            printf("Miss");
        }
        struct node* temp=head->next;
        printf("\t[ ");
        for(int i=0;i<frames;i++)
        {
            temp?printf("%d ",temp->page):printf("-");
            if(temp)temp=temp->next;
        }
        printf("]\n");

    }
    printf("\nTotal page hits: %d\n",ph);
    printf("Total page misses: %d\n",pf);
    
}
void main()
{
    int n,frames;
    printf("Enter number of pages: ");
    scanf("%d",&n);
    int pages[n];
    printf("Enter reference string:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d",&frames);
    head=createNode(-1);
    LFU(pages,n,frames);
}