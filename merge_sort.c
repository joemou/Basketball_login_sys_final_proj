#include "basic_lib.h"
#include "merge_sort.h"

typedef struct node{
    char name[25];
    int score;
    int height;

    struct node *next;//for link list pointer

    struct node *right;//for avl tree pointer
    struct node *left;
} node;

void split(node *first, node **a, node **b){

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

node *merge(node *a, node *b){

    node *result;

    if(a == NULL){
        return b;
    }
    if(b == NULL){
        return a;
    }

    if(a->score > b->score){
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

    if((first==NULL) || (first->next==NULL)){
        return;
    }

    split(first, &a, &b);

    mergesort(&a);
    mergesort(&b);

    *head = merge(a, b);
}