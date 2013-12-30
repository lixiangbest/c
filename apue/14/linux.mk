include ../Make.defines.linux

EXTRALIBS = -pthread

PROGS = 01_nonblockw 02_read 03_deadlock lock 04_childlock\
		endlock 05_mandatory 06_stream fd_set 07_mcopy\
		re_lock relock sleep_us fdsize pipe_buf mmap mwrite

all: ${PROGS}

putenv_r.o: putenv_r.c

01_init: 01_init.o init.o
		$(CC) $(CFLAGS) init.o 01_init.o $(LDFLAGS) $(LDLIBS) -o 01_init

02_reread: 02_reread.o lockfile.o init.o single.o
		$(CC) $(CFLAGS) 02_reread.o lockfile.o init.o single.o $(LDFLAGS) $(LDLIBS) -o 02_reread

03_reread: 03_reread.o lockfile.o init.o single.o
		$(CC) $(CFLAGS) 03_reread.o lockfile.o init.o single.o $(LDFLAGS) $(LDLIBS) -o 03_reread

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o
