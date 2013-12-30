include ../Make.defines.linux

PROGS=01_filetype 02_access 03_umask 04_changemod 05_unlink 06_zap\
	  07_ftw 07_ftwu 08_mycd 09_cdpwd 10_devrdev\
	  dirtree

all:${PROGS}

savedid:savedid.o
	$(LINK.c) -o savedid savedid.o $(LDLIBS)

clean:
	rm -f ${PROGS} ${TEMPFILES} file.hole
