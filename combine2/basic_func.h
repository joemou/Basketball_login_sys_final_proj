#ifndef basic_func_h
#define basic_func_h
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

#endif