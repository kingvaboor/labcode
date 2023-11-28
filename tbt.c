#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// Structure for the threaded binary tree node
struct node
{
    int data;
    int lbit, rbit;
    struct node *left, *right;
};

// Function to create a new node and insert it into the threaded binary tree
struct node *TBTcreate(struct node *head, int data);

// Function to perform preorder traversal on the threaded binary tree
void preorderTBT(struct node *head);

// Function to perform inorder traversal on the threaded binary tree
void inorderTBT(struct node *head);

// Function to find the inorder successor of a node in the threaded binary tree
struct node *inorder_succ(struct node *T);

// Function to perform postorder traversal on the threaded binary tree
void postorderTBT(struct node *head);

int main()
{
    struct node *head;

    // Allocate memory for the head of the threaded binary tree
    head = (struct node *)malloc(sizeof(struct node));

    // Initialize the head with dummy values
    head->lbit = head->rbit = 1;
    head->left = head->right = head;

    // Create a threaded binary tree by inserting nodes
    head = TBTcreate(head, 10);
    head = TBTcreate(head, 6);
    head = TBTcreate(head, 15);
    head = TBTcreate(head, 20);
    head = TBTcreate(head, 17);

    // Display the threaded binary tree using different traversal methods
    printf("Preorder traversal: ");
    preorderTBT(head);

    printf("\nInorder traversal: ");
    inorderTBT(head);

    printf("\nPostorder traversal: ");
    postorderTBT(head->left);

    return 0;
}

// Function to create a new node and insert it into the threaded binary tree
struct node *TBTcreate(struct node *head, int data)
{
    struct node *temp, *p, *q;

    // Allocate memory for the new node
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->lbit = temp->rbit = 0;

    // Check if the tree is empty
    if (head->left == head)
    {
        temp->left = head;
        temp->right = head;
        head->left = temp;
        return head;
    }

    // Traverse the tree to find the correct position for the new node
    p = head->left;
    while (1)
    {
        if (data < p->data && p->lbit == 1)
        {
            p = p->left;
        }
        else if (data > p->data && p->rbit == 1)
        {
            p = p->right;
        }
        else
        {
            break;
        }
    }

    // Update the pointers to insert the new node
    q = p;
    if (data > q->data)
    {
        temp->right = q->right;
        temp->left = q;
        q->right = temp;
        q->rbit = 1;
    }
    else
    {
        temp->left = q->left;
        temp->right = q;
        q->left = temp;
        q->lbit = 1;
    }

    return head;
}

// Function to perform preorder traversal on the threaded binary tree
void preorderTBT(struct node *head)
{
    struct node *T;

    // Start from the leftmost node
    T = head->left;

    while (T != head)
    {
        printf("%d ", T->data);

        // Move to the left child if it exists
        if (T->lbit == 1)
        {
            T = T->left;
        }
        // Move to the right child if it exists
        else if (T->rbit == 1)
        {
            T = T->right;
        }
        // If there is no left or right child, move to the threaded node
        else
        {
            while (T->rbit == 0)
            {
                T = T->right;
            }
            T = T->right;
        }
    }
}

// Function to perform inorder traversal on the threaded binary tree
void inorderTBT(struct node *head)
{
    struct node *T;

    // Start from the leftmost node
    T = head->left;

    // Move to the leftmost leaf node
    while (T->lbit == 1)
    {
        T = T->left;
    }

    // Traverse the threaded binary tree in inorder
    while (T != head)
    {
        printf("%d ", T->data);

        // Move to the inorder successor
        T = inorder_succ(T);
    }
}

// Function to find the inorder successor of a node in the threaded binary tree
struct node *inorder_succ(struct node *T)
{
    if (T->rbit == 0)
    {
        return (T->right);
    }

    // If there is a right child, find the leftmost node in the right subtree
    if (T->rbit == 1)
    {
        T = T->right;
        while (T->lbit == 1)
        {
            T = T->left;
        }
        return T;
    }
}

// Function to perform postorder traversal on the threaded binary tree
void postorderTBT(struct node *head)
{
    // Base case: if the tree is empty, return
    if (head->lbit == 1)
    {
        postorderTBT(head->left);
    }
    if (head->rbit == 1)
    {
        postorderTBT(head->right);
    }
    printf("%d ", head->data);
}
