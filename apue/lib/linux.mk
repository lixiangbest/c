include ../Make.defines.linux

#
# Makefile for misc library.
#

AR=ar
LIBMISC=libapue.a
OBJS=error.o pathalloc.o openmax.o\
	 setfl.o prexit.o tellwait.o\
	 prmask.o signal.o signalintr.o\
	 sleep.o clrfl.o lockreg.o locktest.o\
	 readn.o writen.o popen.o daemonize.o\
	 cliconn.o sendfd.o recvfd.o senderr.o spipe.o\
	 bufargs.o errorlog.o ttymodes.o linux_ptyopen.o\
	 ptyfork.o

RANLIB=ranlib

all:${OBJS}
	${AR} rv ${LIBMISC} $?
	${RANLIB} ${LIBMISC}

clean:
	rm -f *o a.out core temp.* $(LIBMISC)
