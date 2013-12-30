include ../Make.defines.linux

EXTRA=

PROGS = 01_findsvc daytime ruptime ruptimed ruptimed-fd\
		ruptime-dg ruptimed-dg endian sock_stat sock_cntl\
		sock_select

all: ${PROGS} clconn.o initsrv1.o initsrv2.o async_sock.o

clconn.o: clconn.c

initsrv1.o: initsrv1.c

daytime: daytime.o clconn.o
	$(CC) $(CFLAGS) -o daytime daytime.o clconn.o $(LDFLAGS) $(LDLIBS)

ruptime: ruptime.o clconn.o
	$(CC) $(CFLAGS) -o ruptime ruptime.o clconn.o $(LDFLAGS) $(LDLIBS)

ruptimed: ruptimed.o initsrv1.o
	$(CC) $(CFLAGS) -o ruptimed ruptimed.o initsrv1.o $(LDFLAGS) $(LDLIBS)

ruptimed-fd: ruptimed-fd.o initsrv1.o
	$(CC) $(CFLAGS) -o ruptimed-fd ruptimed-fd.o initsrv1.o $(LDFLAGS) $(LDLIBS)

ruptimed-dg: ruptimed-dg.o initsrv1.o
	$(CC) $(CFLAGS) -o ruptimed-dg ruptimed-dg.o initsrv1.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o
