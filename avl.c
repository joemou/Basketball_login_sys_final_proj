#include "basic_lib.h"
#include "avl.h"

typedef struct node{
    char name[25];
    int score;
    int height;

    struct node *next;//for link list pointer

    struct node *right;//for avl tree pointer
    struct node *left;
} node;

void create(node **head, char *name, int score){
    node *temp = (node*) malloc(sizeof(node));
    strcpy(temp->name, name);
    temp->score = score;
    temp->next = NULL;
    temp->right = NULL;
    temp->left = NULL;
    temp->height = 1;   

    if(*head==NULL){
        *head = temp;
    }
    else{
        temp->next = *head;
        *head = temp;
    }
}

void *delete_on_linklist(node **head, char *name){
    node *temp1 = *head;
    if(strcmp(temp1->name,name) == 0){ //forget
      *head = (*head)->next;
    }
    while(strcmp(temp1->next->name,name) != 0){
      temp1 = temp1->next;
    }
    node *temp2 = temp1->next; //temp2 = n
    temp1->next = temp2->next; //temp1->next = n + 1
    // temp1->next = temp1->next->next
    free(temp2);
}

int height(struct node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct node *RR(struct node *y) {
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct node *LL(struct node *x) {
    struct node *y = x->right;
    struct node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct node *root) {
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

struct node *insert(struct node *root, struct node *node) {
    if (root == NULL)
        return node;

    int flag = strcmp(node->name,root->name);

    if (flag < 0){
        root->left = insert(root->left, node);
    }
    else if (flag > 0){
        root->right = insert(root->right, node);
    }
    else{
        printf("name exist\n");
        return node; // node with same name already exists
    }
    // Update height of this node
    root->height = 1 + max(height(root->left), height(root->right));

    // Check the balance factor and rotate the tree if necessary
    int balance = getBalance(root);

    //right rotation
    if (balance > 1 && strcmp(node->name, root->left->name) < 0)
        return RR(root);
    //left rotation
    if (balance < -1 && strcmp(node->name, root->right->name) > 0)
        return LL(root);
    //left-right rotation
    if (balance > 1 && strcmp(node->name, root->left->name) > 0) {
        root->left = LL(root->left);
        return RR(root);
    }
    //right-left rotaion
    if (balance < -1 && strcmp(node->name, root->right->name) < 0) {
        root->right = RR(root->right);
        return LL(root);
    }
    //if balance no rotation
    return root;
}

//find the min value under specify node
struct node *min_name(struct node *node) {
    struct node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

//delete the node on avl tree and link_list
struct node *delete(struct node **head,struct node *root, char *name){
    // Find the node and delete it
    int flag = strcmp(name,root->name);
    if (root == NULL)
        return root;
    if (flag<0)
        root->left = delete(head,root->left, name);
    else if (flag>0)
        root->right = delete(head,root->right, name);
    //when find it(flag==0)
    else {
        //just has one child and no child
        if ((root->left == NULL) || (root->right == NULL)) {
        struct node *temp = root->left ? root->left : root->right;
        //no child
        if (temp == NULL) {
            temp = root;
            root = NULL;
        }
        //one child 
        else
            *root = *temp;
        free(temp);
        }
        //two children 
        else {
        //find the right child then its leftest side(i norder) making it banlance
        struct node *temp = min_name(root->right);

        //copy the temp data and rewrite root
        strcpy(root->name, temp->name);
        root->score = temp->score;
        /*
        //deal with linkedlist part
        node *temp2 = *head;
        if(temp==temp2){
            temp2 = temp2->next;
        }
        else{
            while(temp2->next!=temp){
            temp2 = temp2->next;
            }
            temp2->next = temp->next;
        }*/

        //delete the temp data cuz its had been copy to root
        root->right = delete(head,root->right, temp->name);

        }
    }

    //rebanlance tree
    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left),height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return RR(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = LL(root->left);
        return RR(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return LL(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = RR(root->right);
        return LL(root);
    }

    return root;
}

void print_player(node *node){
    printf("%s %d",node->name,node->score);
} 

void AVL_STRING_SEARCH(node *root,char *name){
    int flag = strcmp(name, root->name);
    if (root==NULL){
        printf("Not found\n");
    }
    else if(flag==0){
        print_player(root);
    }
    else if(flag<0){
        return AVL_STRING_SEARCH(root->left, name);
    }
    else{
        return AVL_STRING_SEARCH(root->right, name);
    }
}

/*for inorder traversal*/
//print order by alphabet
void printInorder(struct node* node)
{
    if (node == NULL){
        return;
    }
    printInorder(node->left);
    printf("%s %d\n", node->name,node->score);
    printInorder(node->right);
}

/*for printing linklist */
void print_linklist(node *head){
    node *temp = head;
    printf("name score\n");
    while(temp!=NULL){
        printf("%s %d\n",temp->name,temp->score);
        temp = temp->next;
  }
}