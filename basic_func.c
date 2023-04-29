#include "basic_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
    char name[25];
    int score;

    int height;
    struct node *next;
    struct node *right;
    struct node *left;
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
    if(head==NULL){
        *head = temp;
    }
    else{
        temp->next = *head;
        *head = temp;
    }
}


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

/*for AVL tree*/

void AVL_STRING_INSERTION(node **root){

}

void AVL_STRING_DELETION(node **root){
    if(root==NULL){
        root = getnode(data);
    }
    else if(data<=root->data){
        root->left = insert(root->left, data);
    }
    else{
        root->right = insert(root->right, data);
    }
    return root;

}

void print_player(node *node){


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




void print_linklist(node **head){

    node *temp = *head;
    printf("name score\n");
    while(temp!=NULL){
        printf("%s %d\n",temp->name,temp->score);
        temp = temp->next;
    }
}
