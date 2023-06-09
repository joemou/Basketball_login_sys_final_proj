#ifndef merge_sort_h
#define merge_sort_h
#include "basic_func.h"

//for mergesort
/* Find mid and split */
void split(node *first, node **a, node **b);

/* merge the node */
struct node *merge(node *a, node *b, int action);

void mergesort(node **head, int action);

#endif