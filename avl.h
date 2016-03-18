#ifndef _avl_h_
#define _avl_h_

typedef struct nodeAVL* AVL;

/*typedef AVL[26] CATALOG;
*/
static AVL rightRotate(AVL y);
static AVL leftRotate(AVL x);
static int getBalance(AVL N);
static AVL newNode(char* string);
static int max(int a, int b);
static int height(AVL n);
AVL insert(AVL node, char* string);
int lookUp(AVL node, char* value);
void preOrder(AVL root);

#endif