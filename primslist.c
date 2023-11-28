#include <stdio.h>
#include <stdlib.h>

// Maximum number of vertices in the graph
#define MAX_VERTICES 10

// Structure to represent a node in the adjacency list
struct node
{
    int vertex;
    int distance;
    struct node *next;
} A[MAX_VERTICES];

// Function declarations
void adj_list(struct node *A[]);
void prims(struct node *A[]);
int Min(int dist[], int visited[]);
int printMST(int parent[]);

int n; // Number of vertices

int main()
{
    n = 5;
    adj_list(A);
    prims(A);
    return 0;
}

// Function to create an adjacency list representation of the graph
void adj_list(struct node *A[])
{
    struct node *p, *new;
    int v1, v2, i = 1, wt;

    printf("Total number of edges: ");
    scanf("%d", &n);

    do
    {
        printf("Enter Edge and weight: ");
        scanf("%d %d %d", &v1, &v2, &wt);

        // Create a new node for v2 and add to the adjacency list of v1
        new = (struct node *)malloc(sizeof(struct node));
        new->vertex = v2;
        new->distance = wt;
        new->next = NULL;
        p = A[v1];
        if (p == NULL)
        {
            A[v1] = new;
        }
        else
        {
            while (p->next != NULL)
                p = p->next;
            p->next = new;
        }

        // Create a new node for v1 and add to the adjacency list of v2
        new = (struct node *)malloc(sizeof(struct node));
        new->vertex = v1;
        new->distance = wt;
        new->next = NULL;
        p = A[v2];
        if (p == NULL)
        {
            A[v2] = new;
        }
        else
        {
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = new;
        }

        i++;
    } while (i <= n);
}

// Function to find the index of the minimum distance vertex
int Min(int dist[], int visited[])
{
    int index, min = 99;

    for (int i = 0; i < n; i++)
    {
        if (dist[i] < min && visited[i] == 0)
        {
            min = dist[i];
            index = i;
        }
    }

    return index;
}

// Function to perform Prim's algorithm
void prims(struct node *A[])
{
    int visited[10], dist[10], parent[10];
    int u, v;
    struct node *p;

    // Initialize arrays
    for (int i = 0; i <= n; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
        dist[i] = 99;
    }

    printf("Enter the start vertex: ");
    scanf("%d", &v);
    dist[v] = 0;

    // Loop to find the minimum spanning tree
    for (int i = 0; i < n - 1; i++)
    {
        u = Min(dist, visited);
        visited[v] = 1;
        p = A[u];

        // Update distance and parent values for adjacent vertices
        while (p != NULL)
        {
            if (p->distance < dist[p->vertex] && visited[p->vertex] == 0)
            {
                dist[p->vertex] = p->distance;
                parent[p->vertex] = u;
            }
            p = p->next;
        }
    }

    // Print the minimum spanning tree
    printMST(parent);
}

// Function to print the minimum spanning tree
int printMST(int parent[])
{
    printf("\nEdge \n");

    for (int i = 1; i < n; i++)
    {
        printf("%d - %d \t \n", parent[i], i);
    }
}
