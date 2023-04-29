#include "basic_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
    char name[25];
    int score;
    struct node *next;
    struct node *left;
    struct node *right;
} node;

//insert node at head

void create(node **head,char *name,int score){
    node *temp = (node *)malloc(sizeof(node));
    strcpy(temp->name, name);
    temp->score = score;
    temp->next = NULL;
    temp->right = NULL;
    temp->left = NULL;
    if(head==NULL){
        *head = temp;
    }
    else{
        temp->next = *head;
        *head = temp;
    }
}



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

void print(node **head){

    node *temp = *head;
    printf("name score\n");
    while(temp!=NULL){
        printf("%s %d\n",temp->name,temp->score);
        temp = temp->next;
    }
}