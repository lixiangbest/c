include ../Make.defines

LDLIBS = -lpcap -lpthread

PROGS = simple_pcap new_pcap loop_pcap filter_pcap

all: ${PROGS}

#unixstrserv02: unixstrserv02.o readcred.o strecho.o
#	${CC} ${CFLAGS} -o $@ unixstrserv02.o readcred.o strecho.o ${LDLIBS}

clean:
	rm -f ${PROGS} ${TEST}
