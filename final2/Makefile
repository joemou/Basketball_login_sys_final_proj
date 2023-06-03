CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

log_in: log_in.o sign_in.o edit_json.o cJSON.o after.o
	gcc ${CFLAGS} -o log_in log_in.o sign_in.o edit_json.o cJSON.o after.o ${LIBS}
 
log_in.o: log_in.c after.h sign_in.h
	gcc ${CFLAGS} -c log_in.c ${LIBS}

sign_in.o: sign_in.c sign_in.h edit_json.h
	gcc ${CFLAGS} -c sign_in.c ${LIBS}

edit_json.o: edit_json.c edit_json.h cJSON.h
	gcc -c edit_json.c

cJSON.o: cJSON.c cJSON.h
	gcc -c  cJSON.c

after.o: after.c after.h sign_in.h edit_json.h cJSON.h
	gcc ${CFLAGS} -c after.c ${LIBS}