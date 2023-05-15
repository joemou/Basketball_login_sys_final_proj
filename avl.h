
node;

/*AVL : Create node for AVL tree.*/
void create(node **head, char *name, int score);

/*AVL : Delete specific data.*/
void *delete_on_linklist(node **head, char *name);

/*AVL : Return heght of tree.*/
int height(struct node *node);

/*AVL : Compare two integer.*/
int max(int a, int b);

/*AVL : Right rotate.*/
struct node *RR(struct node *y);

/*AVL : Get balance factor.*/
int getBalance(struct node *root);

/*AVL : Insert.*/
struct node *insert(struct node *root, struct node *node);

/*AVL : Find min value under specify node.*/
struct node *min_name(struct node *node);

/*AVL : Delete node on both AVL tree and linked_list.*/
struct node *delete(struct node **head, struct node *root, char *name);

/*AVL : Print player data on note.*/
void print_player(node *node);

/*AVL : Search string in AVL tree.*/
void AVL_STRING_SEARCH(node *root,char *name);

/**/
void printInorder(struct node* node);

/*AVL : print linked-list*/
void print_linklist(node *head);