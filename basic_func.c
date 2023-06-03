#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  char name[25];
  int game_played;
  float feiled_goal_percentage;
  float three_point_percentage;
  float points_per_game;
  float steal_per_game;

  int height;
  
  struct node *next;//for link list pointer
  
  struct node *right;//for avl tree pointer
  struct node *left;
} node;

//for crate node
void create(node **head, char *name, int game_played,float feiled_goal_percentage,float three_point_percentage,float points_per_game,float steal_per_game);

//for mergesort
void split(node *first, node **a, node **b);
struct node *merge(node *a, node *b,int action);
void mergesort(node **head,int action);

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
void create(node **head, char *name, int game_played,float feiled_goal_percentage,float three_point_percentage,float points_per_game,float steal_per_game){
  node *temp = (node *)malloc(sizeof(node));
  
  strcpy(temp->name, name);
  temp->game_played = game_played;
  temp->feiled_goal_percentage = feiled_goal_percentage;
  temp->three_point_percentage = three_point_percentage;
  temp->points_per_game = points_per_game;
  temp->steal_per_game = steal_per_game;

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
struct node *merge(node *a,node *b,int action){

  node *result;

  if(a==NULL){
    return b;
  }
  if(b==NULL){
    return a;
  }

  float x = -1, y = -1;

  switch(action){
    case 1:
      x = a->game_played;
      y = b->game_played;
      break; 
    case 2:
      x = a->feiled_goal_percentage;
      y = b->feiled_goal_percentage;
      break;
    case 3:
      x = a->three_point_percentage;
      y = b->three_point_percentage;
      break;
    case 4:
      x = a->points_per_game;
      y = b->points_per_game;
      break;
    case 5:
      x = a->steal_per_game;
      y = b->steal_per_game;
      break;
  }

  if(x>y){
    result = a;
    result->next = merge(a->next, b,action);
  }
  else{
    result = b;
    result->next = merge(b->next, a,action);
  }

  return result;
}
void mergesort (node **head,int action){
  node *first = *head;
  node *a;
  node *b;

  if((first==NULL)||(first->next==NULL)){
    return;
  }

  split(first, &a, &b);

  mergesort(&a,action);
  mergesort(&b,action);

  

  *head = merge(a,b,action);
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
  printf("%s %d %.2f %.2f %.2f %.2f\n",node->name,node->game_played,node->feiled_goal_percentage,node->three_point_percentage,node->points_per_game,node->steal_per_game);
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
      root->game_played = temp->game_played;

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
  printf("%s %d %.2f %.2f %.2f %.2f\n",node->name,node->game_played,node->feiled_goal_percentage,node->three_point_percentage,node->points_per_game,node->steal_per_game);
} 

void AVL_STRING_SEARCH(node *root,char *name){

  if(root==NULL){
    printf("not found");
    return;
  }

  int flag = strcmp(name, root->name);
  
  if(flag==0){
    print_player(root);
    return;
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
  printf("\n");
  while(temp!=NULL){
    printf("%s %d %.2f %.2f %.2f %.2f\n",temp->name,temp->game_played,temp->feiled_goal_percentage,temp->three_point_percentage,temp->points_per_game,temp->steal_per_game);
    temp = temp->next;
  }
}
/*end for printing linklist*/

int main(){
  int time,game_played;
  float feiled_goal_percentage, three_point_percentage, points_per_game, steal_per_game;

  printf("Number of records you want to key in:");
  scanf("%d", &time);
  
  node *head = NULL;
  node *root = NULL;

  char name[25];

  while(time--){
    printf("Enter name & game_played:");
    scanf(" %s %d %f %f %f %f", name, &game_played, &feiled_goal_percentage, &three_point_percentage, &points_per_game, &steal_per_game);
    create(&head, name, game_played, feiled_goal_percentage, three_point_percentage, points_per_game, steal_per_game);//create link list
    root = insert(root,head);//create avl tree
  }

  int action = -1;
  char search_name[25];
  printf("\n0.exit\n");
  printf("1.print player\n");
  printf("2.print player orederd by name alphabet(INORDER)(From AVL TREE)\n");
  printf("3.insert the player\n");
  printf("4.delete the player by input name\n");
  printf("5.search player by input name\n");
  printf("6.change order(sort by what u want)\n\n");
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
        printf("Enter name & game_played:");
        scanf(" %s %d %f %f %f %f", name, &game_played, &feiled_goal_percentage, &three_point_percentage, &points_per_game, &steal_per_game);
        create(&head, name, game_played, feiled_goal_percentage, three_point_percentage, points_per_game, steal_per_game);//create link list
        root = insert(root,head);//create avl tree
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
      case 6:
        printf("ordered by what?\n");
        printf("1.game_played\n2.feiled_goal_percentage\n3.three_point_percentage\n4.points_per_game\n5.float steal_per_game\n\naction:");
        scanf("%d",&action);
        mergesort(&head,action);
        printf("\nordered compeleted\n\n");
        print_linklist(head);
        break;
    }
    
    printf("\n0.exit\n");
    printf("1.print player\n");
    printf("2.print player orederd by name alphabet(INORDER)(From AVL TREE)\n");
    printf("3.insert the player\n");
    printf("4.delete the player by input name\n");
    printf("5.search player by input name\n");
    printf("6.change order(sort by what u want)\n\n");
    printf("\naction: ");
  }
}

/*

test case:

25
joe_mou 75 0.526 0.382 22.4 1.8
alex_lee 62 0.483 0.321 18.6 1.2
david_wu 81 0.572 0.401 25.8 1.5
chris_tan 68 0.507 0.349 16.2 1.1
eric_zhang 70 0.543 0.398 19.9 1.4
jason_li 79 0.526 0.365 20.5 1.3
matt_wang 77 0.519 0.392 17.8 0.9
ben_chen 73 0.508 0.333 15.7 0.8
kevin_huang 67 0.490 0.314 13.4 0.7
ryan_yu 80 0.538 0.401 21.6 1.6
nick_lin 72 0.501 0.361 14.9 1.0
sam_wei 69 0.486 0.329 12.8 0.6
andrew_ma 76 0.518 0.394 18.2 0.9
mark_gao 65 0.475 0.305 11.5 0.5
sean_liu 74 0.532 0.378 19.1 1.2
tim_cheng 71 0.504 0.356 13.8 0.7
daniel_ho 78 0.529 0.388 20.9 1.4
justin_su 66 0.481 0.315 12.1 0.6
adam_chu 82 0.559 0.413 23.7 1.7
jerry_wong 63 0.495 0.338 15.1 1.0
tony_luo 68 0.507 0.359 14.6 1.1
steve_wang 75 0.526 0.382 16.9 0.8
brian_zhu 70 0.511 0.368 13.7 0.7
alex_liu 77 0.532 0.394 19.8 1.3
david_chen 72 0.500 0.354 15.3 0.9


*/
