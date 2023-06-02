sign_in: sign_in.o edit_json.o cJSON.o
	gcc -o sign_in sign_in.o edit_json.o cJSON.o

sign_in.o: sign_in.c sign_in.h edit_json.h
	gcc -c sign_in.c

edit_json.o: edit_json.c edit_json.h cJSON.h
	gcc -c edit_json.c

cJSON.o: cJSON.c cJSON.h
	gcc -c cJSON.c