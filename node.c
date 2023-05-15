#include "node.h"

typedef struct{
    char name[25];
    int score;
    int height;

    struct node *next;//for link list pointer

    struct node *right;//for avl tree pointer
    struct node *left;
} node;