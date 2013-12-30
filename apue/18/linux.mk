include ../Make.defines.linux

PROGS = 01_settty 02_csize 03_ctermid 04_isatty\
		t_ttyname t_getpass t_raw winch reset

all:${PROGS}

t_ttyname: t_ttyname.o ttyname.o

clean:
	rm -f ${PROGS} ${TEMPFILES}
