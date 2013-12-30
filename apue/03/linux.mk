include ../Make.defines.linux

PROGS=01_seek 02_hole 03_mycat 04_fileflags

all:${PROGS}

savedid:savedid.o
	$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES} file.hole
