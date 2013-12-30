include ../Make.defines.linux

EXTRA=

PROGS = 01_pipe pipe1 02_pipe 03_popen myuclc 04_popen\
		05_add 05_addstdio 06_pipe 07_tshm 08_devzero\
		09_pipe 10_popen 11_fifo server_fifo client_fifo\
		server client

all: ${PROGS}

tellwait.o: tellwait.c

clean:
	rm -f ${PROGS} ${TEMPFILES} *.o
