include ../Make.defines.linux
EXTRA=
EXTRALIBS=-pthread

PROGS = getcon timeout suspend atfork getenv

all: detach.o getenv1.o getenv2.o getenv3.o putenv_r.o ${PROGS}

detach.o: detach.c

timeout.o: timeout.c

getenv1.o: getenv1.c

getenv2.o: getenv2.c

putenv_r.o: putenv_r.c

timeout: timeout.o detach.o
		$(CC) $(CFLAGS) timeout.o detach.o $(LDFLAGS) $(LDLIBS) -o timeout

getenv: getenv.o getenv3.o
		$(CC) $(CFLAGS) getenv.o getenv3.o $(LDFLAGS) $(LDLIBS) -o getenv

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o
