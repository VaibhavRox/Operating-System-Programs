#include <stdio.h>
#include <stdlib.h>
struct node
{
    int page;
    struct node *prev,*next;
}*head,*tail;
struct node *createnode(int page)
{
    struct node* newNode=(struct node*)malloc(sizeof(struct node));
    newNode->page=page;
    newNode->prev=newNode->next=NULL;
    return newNode;
}
//Function to insert node at top(MRU)
void pushToTop(struct node* node)
{
    node->next=head->next;
    node->prev=head;
    if(head->next)
    {
        head->next->prev=node;
    }
    head->next=node;
    if(tail==head)
    {
        tail=node;  //if first insertion
    }
}
//Functoin to delete Least Recently Used(LRU) Tail node
void deleteLRU()
{
    if(tail==head) return; //No pages in list
    struct node *temp=tail;
    tail=tail->prev;
    tail->next=NULL;
    free(temp);
}
//Function to move node to top if its already in list
void moveToTop(struct node * node)
{
    if(node->prev) node->prev->next=node->next;
    if(node->next) node->next->prev=node->prev;
    if(node==tail)
    {
        tail=node->prev;  //update tail
    }
    pushToTop(node);
}
//Function to search a page
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
//LRU implementation
void LRU(int pages[],int n,int capacity)
{
    int pageFaults=0,pageHits=0,count=0;
    printf("Page\tFrame\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t",pages[i]);
        struct node* existing=search(pages[i]);
        if(existing)
        {
            pageHits++;
            moveToTop(existing);
            printf("Hit");
        }
        else
        {
            pageFaults++;
            if(count==capacity)
            {
                deleteLRU(); //remove LRU page when full
                count--;
            }
            struct node* newNode=createnode(pages[i]);
            pushToTop(newNode);
            count++;
            printf("Miss");
        }
        //printing stack
        struct node* temp=head->next;
        printf("\t[ ");
        while(temp)
        {
            printf("%d ",temp->page);
            temp=temp->next;
        }
        printf("]\n");
    }
    printf("\nTotal page hits: %d\n",pageHits);
    printf("Total page misses: %d\n",pageFaults);
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
    head=createnode(-1);
    tail=head;
    LRU(pages,n,frames);
}