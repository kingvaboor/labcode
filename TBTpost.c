#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include<GL\glut.h>

// Menu Driven Program with implementation of BST and all the fuctions
// Insert
// Traversal(both without using stack)
// preorder
// inorder
// postorder
// Delete
// Exit Program

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure representing a node in the threaded binary search tree
struct node
{
    int val;
    bool lbit; // left thread indicator
    bool rbit; // right thread indicator

    struct node *left;  // left child pointer
    struct node *right; // right child pointer
};

// Function prototypes
struct node *getNode(int val);
struct node *insert(struct node *head, int key);

struct node *inorderPredecessor(struct node *p);
struct node *inorderSuccessor(struct node *p);

void Traversal(struct node *head);
void inorder(struct node *head);
void preorder(struct node *head);

struct node *findParent(struct node *p);
struct node *postSuccessor(struct node *p);
void postorder(struct node *head);

// Delete function prototypes
struct node *delThreadedBST(struct node *head, int key);
struct node *delTwoChild(struct node *head, struct node *par, struct node *ptr);
struct node *delOneChild(struct node *head, struct node *par, struct node *ptr);
struct node *delNoChild(struct node *head, struct node *par, struct node *ptr);

// Main function
int main()
{
    // Initialization of the threaded binary search tree
    struct node *head;
    head = (struct node *)malloc(sizeof(struct node));
    head->lbit = 0;
    head->rbit = 1;
    head->right = head;
    head->left = head;

    // Uncomment the following to create a sample tree
    // insert(head, 10);
    // insert(head, 5);
    // ...

    // Menu-driven approach for tree operations
    while (1)
    {
        printf("\n\n\n\n****************************************************************");
        printf("\nSelect operation");
        printf("\n\t1.Insert\n\t2.Traverse(pre in)\n\t3.Delete\n\n\t0.Exit\n\nEnter your choice: ");
        int n;
        scanf("%d", &n);
        int temp;

        switch (n)
        {
        case 1:
        {
            printf("\nEnter number to Insert: ");
            scanf("%d", &temp);
            head = insert(head, temp);
        }
        break;

        case 2:
            Traversal(head);
            break;

        case 3:
        {
            printf("\nEnter number to Delete: ");
            scanf("%d", &temp);
            head = delThreadedBST(head, temp);
        }
        break;

        case 0:
            exit(0);
            break;

        default:
            printf("Invalid Choice.");
            break;
        }
    }

    return 0;
}

// Functions for creating a new node and inserting into the threaded binary search tree
struct node *getNode(int val)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->val = val;
    temp->lbit = 0;
    temp->rbit = 0;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct node *insert(struct node *head, int key)
{
    // Function to insert a key into the threaded binary search tree
    struct node *temp = getNode(key);
    struct node *p;

    if (head->left == head)
    {
        head->left = temp;
        temp->left = head;
        temp->right = head;
        return head;
    }

    p = head->left;

    while (1)
    {
        if (key < p->val && p->lbit == 1)
            p = p->left;
        else if (key > p->val && p->rbit == 1)
            p = p->right;
        else
            break;
    }

    if (key < p->val)
    {
        p->lbit = 1;
        temp->left = p->left;
        temp->right = p;
        p->left = temp;
    }
    else if (key > p->val)
    {
        p->rbit = 1;
        temp->right = p->right;
        temp->left = p;
        p->right = temp;
    }

    return head;
}

// Functions for finding the inorder predecessor and successor
struct node *inorderPredecessor(struct node *p)
{
    // Function to find the inorder predecessor of a node
    if (p->lbit == 0)
        return p->left;
    else if (p->lbit == 1)
    {
        p = p->left;
        while (p->rbit == 1)
            p = p->right;
    }
    return p;
}

struct node *inorderSuccessor(struct node *p)
{
    // Function to find the inorder successor of a node
    if (p->rbit == 0)
        return p->right;
    else if (p->rbit == 1)
    {
        p = p->right;
        while (p->lbit == 1)
            p = p->left;
    }
    return p;
}

// Functions for tree traversal (inorder, preorder, postorder)
void inorder(struct node *head)
{
    // Function to perform inorder traversal
    struct node *p;
    p = head->left;
    while (p->lbit == 1)
        p = p->left;

    while (p != head)
    {
        printf(" %d", p->val);
        p = inorderSuccessor(p);
    }
}

void preorder(struct node *head)
{
    // Function to perform preorder traversal
    struct node *p;
    p = head->left;

    while (p != head)
    {
        printf("%d ", p->val);

        if (p->lbit == 1)
        {
            p = p->left;
        }
        else if (p->rbit == 1)
        {
            p = p->right;
        }
        else if (p->rbit == 0)
        {
            while (p->rbit == 0)
                p = p->right;
            p = p->right;
        }
    }
}

struct node *findParent(struct node *p)
{
    // Function to find the parent of a node
    struct node *child = p;
    while (p->rbit == 1)
        p = p->right;
    p = p->right;

    if (p->left == child)
        return p;

    p = p->left;
    while (p->right != child)
    {
        p = p->right;
    }
    return p;
}

struct node *postSuccessor(struct node *p)
{
    // Function to find the postorder successor of a node
    struct node *cur = p;
    struct node *parent = findParent(cur);

    if (parent->right == cur)
        return parent;
    else
    {
        while (p->rbit == 1)
            p = p->right;
        p = p->right;

        if (p->rbit == 1)
        {
            p = p->right;
            while (!(p->rbit == 0 && p->lbit == 0))
            {
                if (p->lbit == 1)
                    p = p->left;
                else if (p->rbit == 1)
                    p = p->right;
            }
        }
    }
    return p;
}

void postorder(struct node *head)
{
    // Function to perform postorder traversal
    struct node *p = head->left;
    struct node *temp = p;
    while (!(p->rbit == 0 && p->lbit == 0))
    {
        if (p->lbit == 1)
        {
            p = p->left;
        }
        else if (p->rbit == 1)
            p = p->right;
    }
    printf(" %d", p->val);

    while (p != head->left)
    {
        p = postSuccessor(p);
        printf(" %d", p->val);
    }
}

void Traversal(struct node *head)
{
    // Function to select traversal type (preorder, inorder, postorder)
    printf("\nTraversal Type : \n1.preorder\n2.Inorder\n3.PostOrder\n\n\nEnter your choice: ");
    int n;
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        printf("\nPreorder:\n\t");
        preorder(head);
        break;

    case 2:
        printf("\nInorder:\n\t");
        inorder(head);
        break;

    case 3:
        printf("\nPostorder:\n\t");
        postorder(head);
        break;

    default:
        break;
    }
}

// Functions for deleting a node from the threaded binary search tree
struct node *delThreadedBST(struct node *head, int key)
{
    // Function to delete a node from the threaded binary search tree
    struct node *par = head, *ptr = head->left;
    bool found = 0;

    while (ptr != head)
    {
        if (key == ptr->val)
        {
            found = 1;
            break;
        }
        par = ptr;
        if (key < ptr->val)
        {
            if (ptr->lbit == 1)
                ptr = ptr->left;
            else
                break;
        }
        else
        {
            if (ptr->rbit == 1)
                ptr = ptr->right;
            else
                break;
        }
    }

    if (found == 0)
        printf("key not present in tree\n");

    else if (ptr->lbit == 1 && ptr->rbit == 1)
        head = delTwoChild(head, par, ptr);

    else if (ptr->lbit == 0 && ptr->rbit == 0)
        head = delNoChild(head, par, ptr);

    else
        head = delOneChild(head, par, ptr);

    return head;
}

struct node *delTwoChild(struct node *head, struct node *par, struct node *ptr)
{
    // Function to delete a node with two children
    struct node *parSuc = ptr;
    struct node *suc = ptr->right;

    while (suc->lbit == 1)
    {
        parSuc = suc;
        suc = suc->left;
    }

    ptr->val = suc->val;

    if (suc->lbit == 0 && suc->rbit == 0)
        head = delNoChild(head, parSuc, suc);

    else
        head = delOneChild(head, parSuc, suc);

    return head;
}

struct node *delOneChild(struct node *head, struct node *par, struct node *ptr)
{
    // Function to delete a node with one child
    struct node *child;
    if (ptr->lbit == 1)
        child = ptr->left;
    else
        child = ptr->right;

    struct node *p = inorderPredecessor(ptr);
    struct node *s = inorderSuccessor(ptr);

    if (ptr == par->left)
        par->left = child;
    else
        par->right = child;

    if (ptr->lbit == 1)
        p->right = s;

    else if (ptr->rbit == 1)
        s->left = p;

    free(ptr);
    return head;
}

struct node *delNoChild(struct node *head, struct node *par, struct node *ptr)
{
    // Function to delete a node with no children
    if (ptr == head->left)
    {
        ptr = NULL;
    }
    else if (ptr == par->left)
    {
        par->lbit = 0;
        par->left = ptr->left;
    }
    else if (ptr == par->right)
    {
        par->rbit = 0;
        par->right = ptr->right;
    }
    free(ptr);
    return head;
}

