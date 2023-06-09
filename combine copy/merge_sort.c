#include "merge_sort.h"

/*for merge sort*/
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

void mergesort(node **head,int action){
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