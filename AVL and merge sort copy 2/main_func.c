#include "basic_func.h"
#include "avl.h"
#include "merge_sort.h"
#include "cJSON.h"

#define watch_int(x) printf(#x " is %d\n", x)
#define watch_string(x) printf(#x " is %s\n", x)
#define debug printf("Debug line %d\n", __LINE__)

char *read_json_to_str(char *file_name){
    FILE *file = fopen(file_name, "r");

    fseek (file , 0, SEEK_END);
    int size = ftell(file);
    rewind(file);
    char *json_file = (char*) malloc(sizeof(char) * size);
    fread(json_file, 1, size, file);

    fclose(file);
    
    return json_file;
}

int main(){
  int time,game_played;
  float feiled_goal_percentage, three_point_percentage, points_per_game, steal_per_game;

  node *head = NULL;
  node *root = NULL;

  char *name;

  char *data = read_json_to_str("data.json");
  cJSON *team = cJSON_Parse(data);
  cJSON *team1 = cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(team, "Basket_Ball_Teams"), 0), "Players");
  int size = cJSON_GetArraySize(team1);
  printf("%d", size);
  for(int i = 0; i < size; ++i){
    cJSON *tmp = cJSON_GetArrayItem(team1, i);
    name = cJSON_GetStringValue(cJSON_GetObjectItem(tmp, "Name"));
    game_played = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "GP"));
    feiled_goal_percentage = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "FG"));
    three_point_percentage = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "3P"));
    points_per_game = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "PPG"));
    steal_per_game = cJSON_GetNumberValue(cJSON_GetObjectItem(tmp, "SPG"));
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
  return 0;
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
