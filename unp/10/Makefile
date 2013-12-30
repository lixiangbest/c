include ../Make.defines

PROGS = sctpserv01 sctpcli01 sctpserv02 sctpcli02

TEST = sctpdayserv sctpdaycli

LDLIBS += -lm -lsctp

all: ${PROGS} ${TEST}

clean:
	rm -f ${PROGS} ${TEST}
