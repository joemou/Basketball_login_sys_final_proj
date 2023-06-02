
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

Player_Data: log_in.o after.o cJSON.o edit_json.o
	${CC} ${CFLAGS} -o Player_Data log_in.o after.o cJSON.o edit_json.o ${LIBS}

log_in.o: log_in.c after.h
	${CC} ${CFLAGS} -c log_in.c ${LIBS}

after.o: after.c after.h cJSON.h edit_json.h
	${CC} ${CFLAGS} -c after.c ${LIBS}

cJSON.o: cJSON.c cJSON.h
	${CC} -c cJSON.c

edit_json.o: edit_json.c edit_json.h
	${CC} -c edit_json.c

clean: 
	rm ${PROG}