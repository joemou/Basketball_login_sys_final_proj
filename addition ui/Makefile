
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

log_in: log_in.o after.o create_account.o
	${CC} ${CFLAGS} -o log_in log_in.o after.o create_account.o ${LIBS}

log_in.o: log_in.c after.h create_account.h
	${CC} ${CFLAGS} -c log_in.c ${LIBS}

after.o: after.c after.h
	${CC} ${CFLAGS} -c after.c ${LIBS}

create_account.o: create_account.c create_account.h
	${CC} ${CFLAGS} -c create_account.c ${LIBS}

clean: 
	rm ${PROG}