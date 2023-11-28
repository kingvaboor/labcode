#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
struct node
{
    int data;
    struct node *left;
    struct node *right;
};
struct stack
{
    struct node *T;
    struct stack *next;
};
struct stack *top;
struct node *insert(struct node *root, int data);
struct node *newnode(int data);
struct node *deletefy(struct node *root, int data);
void push(struct node *root, struct stack **top);
struct node *pop(struct stack **top);
int emptystack();
struct node *search(struct node *root, int target);
void preorder(struct node *T);
int main()
{
    struct node *root = NULL;
    root = insert(root, 15);
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 35);
    root = insert(root, 5);
    root = insert(root, 17);
    preorder(root);
    root = deletefy(root, 17);
    printf("\n");
    preorder(root);
    // int target = 95;
    // struct node *result = search(root, target);

    // if (result != NULL)
    // {
    //     printf("\n%d found in the BST.\n", target);
    // }
    // else
    // {
    //     printf("\n%d not found in the BST.\n", target);
    //     return 0;
    // }
    return 0;
}
struct node *insert(struct node *root, int data)
{
    if (root == NULL)
    {
        root = newnode(data);
    }
    else
    {
        if (data <= root->data)
        {
            root->left = insert(root->left, data);
        }
        else if (data > root->data)
        {
            root->right = insert(root->right, data);
        }
    }
    return root;
}
struct node *newnode(int data)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}
void push(struct node *root, struct stack **top)
{
    struct stack *temp;
    temp = (struct stack *)malloc(sizeof(struct stack));
    temp->T = root;
    temp->next = *top;
    *top = temp;
}
struct node *pop(struct stack **top)
{
    struct node *p;
    struct stack *temp;
    if (*top == NULL)
    {
        return NULL;
    }
    else
    {
        temp = *top;
        *top = temp->next;
        p = temp->T;
        free(temp);
        return p;
    }
}
int emptystack()
{
    if (top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
struct node *search(struct node *root, int target)
{
    while (root != NULL)
    {
        if (target == root->data)
        {
            return root; // Target found
        }
        else if (target < root->data)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return NULL;
}
void preorder(struct node *T)
{
    while (T != NULL)
    {
        printf("%d ", T->data);
        push(T, &top);
        T = T->left;
    }
    while (!emptystack())
    {
        T = pop(&top);
        T = T->right;
        while (T != NULL)
        {
            printf("%d ", T->data);
            push(T, &top);
            T = T->left;
        }
    }
}
struct node *deletefy(struct node *root, int data)
{
    struct node *current = root;
    struct node *parent = NULL;
    struct stack *p = NULL;
    while (current != NULL && current->data != data)
    {
        push(current, &p);
        parent = current;
        if (data < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    if (current == NULL)
    {
        return root;
    }
    if (current->left == NULL || current->right == NULL)
    {
        struct node *temp = current->left ? current->left : current->right;
        if (temp == NULL)
        {
            temp = current;
            current = NULL;
        }
        else
        {
            *current = *temp;
        }
        free(temp);
    }
    else
    {
        struct node *successor = current->right;
        while (successor->left != NULL)
        {
            push(successor, &p);
            parent = successor;
            successor = successor->left;
        }
        current->data = successor->data;
        if (parent != current)
        {
            parent->left = successor->right;
        }
        else
        {
            parent->right = successor->right;
        }
        free(successor);
    }
    while (!emptystack())
    {
        parent = pop(&p);
        if (parent->left && parent->left->data == data)
        {
            parent->left = current;
        }
        else
        {
            parent->right = current;
        }
    }
    return root;
}