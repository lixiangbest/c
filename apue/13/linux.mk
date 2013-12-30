include ../Make.defines.linux

EXTRALIBS = -pthread

PROGS = 01_init 02_reread 03_reread 04_daemoninit

all: signal runinit ${PROGS}

getenv2.o: getenv2.c

putenv_r.o: putenv_r.c

01_init: 01_init.o init.o
		$(CC) $(CFLAGS) init.o 01_init.o $(LDFLAGS) $(LDLIBS) -o 01_init

02_reread: 02_reread.o lockfile.o init.o single.o
		$(CC) $(CFLAGS) 02_reread.o lockfile.o init.o single.o $(LDFLAGS) $(LDLIBS) -o 02_reread

03_reread: 03_reread.o lockfile.o init.o single.o
		$(CC) $(CFLAGS) 03_reread.o lockfile.o init.o single.o $(LDFLAGS) $(LDLIBS) -o 03_reread

04_daemoninit: 04_daemoninit.o init.o
		$(CC) $(CFLAGS) 04_daemoninit.o init.o $(LDFLAGS) $(LDLIBS) -o 04_daemoninit

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o
