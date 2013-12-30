include ../Make.defines.linux
EXTRA=
EXTRALIBS=-pthread

PROGS = 01_threadid 02_exitstatus 03_badexit 04_cleanup

all: mutex1.o mutex2.o mutex3.o rwlock.o condvar.o ${PROGS}

mutex1.o: mutex1.c

mutex2.o: mutex2.c

mutex3.o: mutex3.c

rwlock.o: rwlock.c

condvar.o: condvar.c

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o
