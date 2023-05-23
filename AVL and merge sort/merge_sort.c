#include "basic_func.h"
#include "merge_sort.h"
#include "node.h"

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