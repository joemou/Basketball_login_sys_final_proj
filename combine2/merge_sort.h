#ifndef merge_sort_h
#define merge_sort_h
#include "basic_func.h"

// for mergesort
/* Find mid and split */
void split(node *first, node **a, node **b);

/* merge the node */
struct node *Merge(node *a, node *b, int action);

void Mergesort(node **head, int action);

#endif
