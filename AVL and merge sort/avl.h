
//for avl tree and search

/* Create node for AVL and linked list (insert node at head) */
void create(node **head, char *name, int score);

/* for inorder traversal, print order by alphabet */
void printInorder(struct node *node);

int height(struct node *node);
int max(int a, int b);

/* Right rotate */
struct node *RR(struct node *y);
/* Left rotate */
struct node *LL(struct node *x);

/* Get the balance factor */
int getBalance(struct node *root);

/* Find the correct position to insert the node and insert it */
struct node *insert(struct node *root, struct node *node);

/* Find the min value under specify node */
struct node *min_name(struct node *node);

/* Delete the node on avl tree and link_list */
struct node *delete(struct node **head, struct node *point, struct node *root, char *name);

/* Printing linklist */
void print_player(node *node);

void AVL_STRING_SEARCH(node *root, char *name);

/* for print */
void print_linklist(node *head);
