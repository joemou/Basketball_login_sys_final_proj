#include "basic_func.h"
#include "avl.h"
#include "merge_sort.h"

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
