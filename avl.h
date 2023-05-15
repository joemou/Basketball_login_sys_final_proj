
node;

/*AVL : Create node for AVL tree*/
void create(node **head, char *name, int score);

/*AVL : Delete specific data*/
void *delete_on_linklist(node **head, char *name);

/*AVL : Return heght of tree*/
int height(struct node *node);

/*AVL : Compare two integer*/
int max(int a, int b);

/*AVL : Right rotate*/
struct node *RR(struct node *y);

/*AVL : Get balance factor*/
int getBalance(struct node *root);

/*AVL : Insert*/
struct node *insert(struct node *root, struct node *node);