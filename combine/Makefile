
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

log_in: log_in.o after.o create_account.o sign_in.o edit_json.o cJSON.o
	${CC} ${CFLAGS} -o log_in log_in.o after.o create_account.o sign_in.o edit_json.o cJSON.o ${LIBS}

log_in.o: log_in.c after.h create_account.h sign_in.h
	${CC} ${CFLAGS} -c log_in.c ${LIBS}

after.o: after.c after.h
	${CC} ${CFLAGS} -c after.c ${LIBS}

create_account.o: create_account.c create_account.h after.h sign_in.h
	${CC} ${CFLAGS} -c create_account.c ${LIBS}

sign_in.o: sign_in.c sign_in.h edit_json.h
	${CC} ${CFLAGS} -c sign_in.c ${LIBS}

edit_json.o: edit_json.c edit_json.h cJSON.h
	${CC} -c edit_json.c

cJSON.o: cJSON.c cJSON.h
	${CC} -c cJSON.c

clean: 
	rm ${PROG}