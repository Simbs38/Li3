#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
    char* string;
    struct node *left;
    struct node *right;
    int height;
};

#define MAX_SIZE 50

struct node *rightRotate(struct node *y);
struct node *leftRotate(struct node *x);
void preOrder(struct node *root);
struct node* insert(struct node* node, char* string);
int getBalance(struct node *N);
struct node* newNode(char* string);
int max(int a, int b);
int height(struct node *n);
int lookUp(struct node *node, char* value);
void preOrder(struct node *root);