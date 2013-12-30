include ../Make.defines

PROGS = unixbind unixstrserv01 unixstrcli01\
		unixdgserv01 unixdgcli01\
		mycat openfile unixstrserv02\
		unixstrcli02 backlog pipe socketpair\

TEST = test

all: ${PROGS} ${TEST}

unixstrserv02: unixstrserv02.o readcred.o strecho.o
	${CC} ${CFLAGS} -o $@ unixstrserv02.o readcred.o strecho.o ${LDLIBS}

clean:
	rm -f ${PROGS} ${TEST}
