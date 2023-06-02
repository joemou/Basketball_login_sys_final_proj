edit_json: edit_json.o cJSON.o
	gcc -o edit_json edit_json.o cJSON.o

edit_json.o: edit_json.c cJSON.h
	gcc -c edit_json.c

cJSON.o: cJSON.c cJSON.h
	gcc -c cJSON.c