include ../Make.defines.linux

PROGS=01_ls 02_cat 03_getputc\
	  04_hello 05_shell 06_error\
	  07_uidgid 08_shellsig

all:${PROGS}

savedid:savedid.o
	$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES} file.hole
