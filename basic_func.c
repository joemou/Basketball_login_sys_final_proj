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
} node;

//for crate node
void create(node **head, char *name, int score);

//for mergesort
void split(node *first, node **a, node **b);
struct node *merge(node *a, node *b);
void mergesort(node **head);

//for avl tree and search
int height(struct node *node);
int max(int a, int b);
struct node *RR(struct node *y);
struct node *LL(struct node *x);
int getBalance(struct node *root);
struct node *insert(struct node *root, struct node *node);
struct node *min_name(struct node *node);
struct node *delete(struct node **head, struct node *point, struct node *root, char *name);
void print_player(node *node);
void AVL_STRING_SEARCH(node *root, char *name);

//for print
void print_linklist(node *head);
void printInorder(struct node *node);

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
struct node *merge(node *a,node *b){

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
/*end for inorder traversal*/


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
  node *y = x->right;
  node *T2 = y->left;

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

// Find the correct position to insert the node and insert it
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
struct node *delete(struct node **head,struct node *point,struct node *root, char *name){
  // Find the node and delete it
  if (root == NULL)
    return root;
  if (strcmp(name,root->name)<0)
    root->left = delete(head,point,root->left, name);
  else if (strcmp(name,root->name)>0)
    root->right = delete(head,point,root->right, name);
  //when find it(flag==0)
  else {
    //just has one child and no child
    if ((root->left == NULL) || (root->right == NULL)) {
      struct node *temp = root->left ? root->left : root->right;


      //deal with linkedlist part
      //no child
      if (temp == NULL) {
        temp = root;

        node *temp2 = point;
        node *prev = NULL;
        if(root==temp2){
          (*head) = (*head)->next;
        }
        else{
          while(temp2!=root){
            prev = temp2;
            temp2 = temp2->next;
          }
          prev->next = temp2->next;
        }

        root = NULL;
      }
      //one child 
      else{

        //cuz next cannot *root = *temp;
        strcpy(root->name, temp->name);
        root->right = temp->right;
        root->left = temp->left;
        root->height = temp->height;

        //deal with linkedlist part
        node *temp2 = point;
        node *prev = NULL;
        if(temp==point){
          (*head) = (*head)->next;
        }
        else{
          while(temp2!=temp){
            prev = temp2;
            temp2 = temp2->next;
          }
          prev->next = temp2->next;
        }

        printf("b\n\n");
      }
      free(temp);
    }
    //two children 
    else {

      //find the right child then its leftest side(i norder) making it banlance
      struct node *temp = min_name(root->right);

      //copy the temp data and rewrite root
      strcpy(root->name, temp->name);
      root->score = temp->score;

      //delete the copied node
      root->right = delete(head, point, root->right, temp->name);
      printf("c\n");
    }

  }

  //rebanlance the tree
  if (root == NULL)
    return root;

  root->height = 1 + max(height(root->left),height(root->right));


  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) > 0){
    printf("aa\n");
    return RR(root);
  }
  if (balance > 1 && getBalance(root->left) < 0) {
    printf("bb\n");
    root->left = LL(root->left);
    return RR(root);
  }

  if (balance < -1 && getBalance(root->right) < 0){
    printf("%d\n",balance);
    return LL(root);
  }
  if (balance < -1 && getBalance(root->right) > 0) {
    printf("dd\n");
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
  if (flag!=0){
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



/*for printing linklist */
void print_linklist(node *head){
  node *temp = head;
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

  int action = -1;
  char search_name[25];
  printf("\n0.exit\n");
  printf("1.print player orederd by socre\n");
  printf("2.print player orederd by name alphabet(INORDER)\n");
  printf("3.insert the player\n");
  printf("4.delete the player by input name\n");
  printf("5.search player by input name\n\n");
  printf("action: ");

  while(scanf("%d",&action)!=0){
    switch(action){
      case 1:
        print_linklist(head);
        break;
      case 2: 
        printInorder(root);
        break;
      case 3:
        printf("Enter name & score:");
        scanf(" %s %d", name, &score);
        create(&head, name, score);//create link list
        root = insert(root,head);//create avl tree
        mergesort(&head);//sort
        printf("inserted successfully\n");
        break;
      case 4:
        printf("plz input the name\n");
        scanf("%s", search_name);
        delete (&head,head,root, search_name);
        printf("deleted successfully\n");
        break;
      case 5:
        printf("plz input the name\n");
        scanf("%s", search_name);
        AVL_STRING_SEARCH(root, search_name);
        break;
    }
    printf("\naction: ");
  }
}

/*

test case:

10
joe 100
bob 45
apple 56
nui 34
kyle 90
aufwiderzen 78
zebra 28
monica 10000
jordan 3232223
hao 100009



5
a 1
b 2
c 3
d 4
e 5
*/
