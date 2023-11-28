#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define max 30
struct vertex
{
    int data;
    struct vertex *next;
};
struct stack
{
    int v;
    struct stack *next;
};
struct stack *top = NULL;
void insertl(int, int, struct vertex[], int);
struct queue
{
    int v;
    struct queue *next;
};
struct queue *front = NULL;
struct queue *rear = NULL;
void enqueue(int);
int notemptyqueue();
int dequeue();
void push(int);
int pop();
int notemptystack();
void bfs(struct vertex[], int);
void dfs(struct vertex[], int);

void bfs(struct vertex graphl[], int n)
{
    int visited[max];
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    int v;
    printf("Enter start vertex : ");
    scanf("%d", &v);
    visited[v] = 1;
}
void push(int v)
{
    struct stack *temp = (struct stack *)malloc(sizeof(struct stack));
    temp->v = v;
    temp->next = top;
    top = temp;
}
int pop()
{
    struct stack *temp = top;
    top = temp->next;
    int n = temp->v;
    free(temp);
    return n;
}
int notemptystack()
{
    return top != NULL;
}
void enqueue(int v)
{
    struct queue *temp = (struct queue *)malloc(sizeof(struct queue));
    temp->v = v;
    temp->next = NULL;
    if (notemptyqueue() == 0)
    {
        rear = temp;
        front = temp;
    }
    else
    {
        rear->next = temp;
        rear = temp;
    }
}
int notemptyqueue()
{
    return ((front != NULL) && (rear != NULL));
}
int dequeue()
{
    if (front != NULL)
    {
        int temp = front->v;
        struct queue *t = front;
        front = front->next;
        if (t == rear)
        {
            rear = NULL;
        }
        free(t);
        return temp;
    }
}
int main()
{
    int v;
    printf("Enter the number of vertices : ");
    scanf("%d", &v);
    struct vertex graphl[max];
    for (int i = 0; i < v; i++)
    {
        graphl[i].data = i;
        graphl[i].next = NULL;
    }
    int exit;
    do
    {
        int exit;
        printf("Do you want to enter an edge (1:Yes 0:No) : ");
        scanf("%d", &exit);
        if (exit)
        {
            int v1, v2;
            printf("Enter vertices of edge :");
            scanf("%d%d", &v1, &v2);
            if (v1 >= v || v2 >= v)
            {
                printf("\nError! number of nodes exceeded!");
                continue;
            }
            insertl(v1, v2, graphl, v);
        }

    } while (exit);
    printf("\nPerforming BFS using adjacency list");
    bfsl(graphl, v);
    printf("\n DFS : ");
    dfsl(graphl, v);
    return 0;
}
void insertl(int v1, int v2, struct vertex graphl[], int v)
{
    struct vertex *temp = (struct vertex *)malloc(sizeof(struct vertex));
    temp->data = v2;
    temp->next = graphl[v1].next;
    graphl[v1].next = temp;
    temp = (struct vertex *)malloc(sizeof(struct vertex));
    temp->data = v1;
    temp->next = graphl[v2].next;
    graphl[v2].next = temp;
}