typedef struct node{
    char name[25];
    int score;
    int height;
    
    struct node *next; //for linked_list pointer
    
    struct node *right; //for avl tree pointer
    struct node *left;
} node;