include ../Make.defines.linux

PROGS= 01_fork 02_vfork 02_vfork1 02_vfork2 03_wait 04_fork\
	   05_tellwait 06_tellwait 06_tellwait1 07_exec\
	   echoall 08_exec 08_exec1 systest1 09_systest\
	   10_pruids 11_testacc 12_pracct 13_times zombie

all:${PROGS} system.o

system.o: system.c

systest1: system.o systest1.o
	$(CC) $(CFLAGS) -o systest1 systest1.o system.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f ${PROGS} *.o
