target = input_player_data

$(target): $(target).o cJSON.o
	gcc -o $(target) $(target).o cJSON.o
	 
cJSON.o: cJSON.c cJSON.h
	gcc -c cJSON.c

$(target).o: $(target).c
	gcc -c $(target).c