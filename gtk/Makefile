
# PROG = log_in

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

# ${PROG}: ${PROG}.c
# 	${CC} ${CFLAGS} -o ${PROG} ${PROG}.c ${LIBS}

log_in: log_in.o after.o
	${CC} ${CFLAGS} -o log_in log_in.o after.o ${LIBS}

log_in.o: log_in.c after.h
	${CC} ${CFLAGS} -c log_in.c ${LIBS}

after.o: after.c after.h
	${CC} ${CFLAGS} -c after.c ${LIBS}

clean: 
	rm ${PROG}