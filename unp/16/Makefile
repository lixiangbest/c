include ../Make.defines

PROGS = tcpcli01 tcpcli02 web\
		tcpservselect01 tcpcli03

TEST = 

all: ${PROGS} ${TEST}

tcpcli01: tcpcli01.o strclifork.o
	${CC} ${CFLAGS} -o $@ tcpcli01.o strclifork.o ${LDLIBS}

tcpcli02: tcpcli02.o strclinonb.o
	${CC} ${CFLAGS} -o $@ tcpcli01.o strclinonb.o ${LDLIBS}

clean:
	rm -f ${PROGS} ${TEST}
