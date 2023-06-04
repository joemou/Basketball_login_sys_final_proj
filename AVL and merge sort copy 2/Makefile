main_func: main_func.o avl.o merge_sort.o cJSON.o
	gcc -o main_func main_func.o avl.o merge_sort.o cJSON.o

main_func.o: main_func.c basic_func.h avl.h merge_sort.h
	gcc -c main_func.c

avl.o: avl.c avl.h basic_func.h
	gcc -c avl.c

merge_sort.o: merge_sort.c merge_sort.h basic_func.h
	gcc -c merge_sort.c

cJSON.o: cJSON.c cJSON.h
	gcc -c cJSON.c