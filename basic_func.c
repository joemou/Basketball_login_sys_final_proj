#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char name[25];
  int score;
  int height;
  
  struct node *next;//for link list pointer
  
  struct node *right;//for avl tree pointer
  struct node *left;

  struct node *level_next;//for avl level order traversl pointer
} node;


/*for create the node*/
//insert node at head
void create(node **head,char *name,int score){
  node *temp = (node *)malloc(sizeof(node));
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
/*end for create the node*/


/*for merge sort*/
//find mid and split
void split(node *first,node **a,node **b){

  node *fast;
  node *slow;

  fast = first->next;
  slow = first;

  while(fast!=NULL){
    fast = fast->next;
    if(fast!=NULL){
      fast = fast->next;
      slow = slow->next;
    }
  }

  *b = slow->next;

  *a = first;
  slow->next = NULL;

    
}
//merge the node
node *merge(node *a,node *b){

  node *result;

  if(a==NULL){
    return b;
  }
  if(b==NULL){
    return a;
  }

  if(a->score>b->score){
    result = a;
    result->next = merge(a->next, b);
  }
  else{
    result = b;
    result->next = merge(b->next, a);
  }

  return result;
}
void mergesort (node **head){
  node *first = *head;
  node *a;
  node *b;

  if((first==NULL)||(first->next==NULL)){
    return;
  }

  split(first, &a, &b);

  mergesort(&a);
  mergesort(&b);

  *head = merge(a,b);
}
/*end for merge sort*/


/*for AVL tree https://www.youtube.com/watch?v=jDM6_TnYIqE*/
//detect height
int height(struct node *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Right rotate
struct node *RR(struct node *y) {
  node *x = y->left;
  node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate
struct node *LL(struct node *x) {
  struct node *y = x->right;
  struct node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(struct node *root) {
  if (root == NULL)
    return 0;
  return height(root->left) - height(root->right);
}

struct node *insert(struct node *root, struct node *node) {
  // Find the correct position to insert the node and insert it
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
    return root; // node with same name already exists
  }
  // Update height of this node
  root->height = 1 + max(height(root->left), height(root->right));

  // Check the balance factor and rotate the tree if necessary
  int balance = getBalance(root);

  if (balance > 1 && strcmp(node->name, root->left->name) < 0)
    return RR(root);

  if (balance < -1 && strcmp(node->name, root->right->name) > 0)
    return LL(root);

  if (balance > 1 && strcmp(node->name, root->left->name) > 0) {
    root->left = LL(root->left);
    return RR(root);
  }

  if (balance < -1 && strcmp(node->name, root->right->name) < 0) {
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
/*end for avl tree*/


/*for inorder traversal*/
//print order by alphabet
void printInorder(struct node* node)
{
  if (node == NULL){
    return;
  }
  printInorder(node->left);
  printf("%s\n", node->name);
  printInorder(node->right);
}
/*end for inorder traversal*/


/*for printing linklist */
void print_linklist(node **head){
  node *temp = *head;
  printf("name score\n");
  while(temp!=NULL){
    printf("%s %d\n",temp->name,temp->score);
    temp = temp->next;
  }
}
/*end for printing linklist*/

int main(){
  int time,score;

  printf("Number of records you want to key in:");
  scanf("%d", &time);
  
  node *head = NULL;
  node *root = NULL;

  char name[25];

  while(time--){
    printf("Enter name & score:");
    scanf(" %s %d", name, &score);
    create(&head, name, score);//create link list

    root = insert(root,head);//create avl tree
  }
  mergesort(&head);

  printInorder(root);
}
