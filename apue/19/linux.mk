include ../Make.defines.linux

PROGS = 01_pts pty getopt sigaction pipestdin\
		select select1

SEGV = segfault1 segfault2 segfault3 segfault4

all:${PROGS} ${SEGV}

pty: main.o
	gcc -o pty main.o $(LDFLAGS) $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o
