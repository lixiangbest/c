include ../Make.defines.linux

EXTRA=
EXTRALIBS=-pthread

PROGS = 01_bindunix duplex_open openclient opend open_dae opend_dae\
		open_log usock_server usock_client

all: ${PROGS} spipe.o servlisten.o servaccept.o cliconn.o\
		sendfd.o recvfd.o sendfd2.o recvfd2.o

spipe.o: spipe.c

servlisten.o: servlisten.c

servaccept.o: servaccept.c

cliconn.o: cliconn.c

sendfd.o: sendfd.c

recvfd.o: recvfd.c

sendfd2.o: sendfd2.c

recvfd2.o: recvfd2.c

daytime: daytime.o clconn.o
	$(CC) $(CFLAGS) -o daytime daytime.o clconn.o $(LDFLAGS) $(LDLIBS)

ruptime: ruptime.o clconn.o
	$(CC) $(CFLAGS) -o ruptime ruptime.o clconn.o $(LDFLAGS) $(LDLIBS)

openclient: openclient.o recvfd.o
	$(CC) $(CFLAGS) -o openclient openclient.o recvfd.o $(LDFLAGS) $(LDLIBS)

opend: opend.o sendfd.o
	$(CC) $(CFLAGS) -o opend opend.o sendfd.o $(LDFLAGS) $(LDLIBS)

open_dae: open_dae.o recvfd.o cliconn.o
	$(CC) $(CFLAGS) -o open_dae open_dae.o recvfd.o cliconn.o $(LDFLAGS) $(LDLIBS)

opend_dae: opend_dae.o sendfd.o servlisten.o servaccept.o
	$(CC) $(CFLAGS) -o opend_dae opend_dae.o sendfd.o servlisten.o servaccept.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o
