main_func: main_func.o avl.o merge_sort.o
	gcc -o main_func main_func.o avl.o merge_sort.o

main_func.o: main_func.c basic_func.h avl.h merge_sort.h node.h
	gcc -c main_func.c

avl.o: avl.c avl.h basic_func.h node.h
	gcc -c avl.c

merge_sort.o: merge_sort.c merge_sort.h basic_func.h node.h
	gcc -c merge_sort.c 