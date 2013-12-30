include ../Make.defines.linux

PROGS=01_getcputc 02_fgetsfputs 03_buf 04_tempfiles 05_tempnam

all:${PROGS}

clean:
	rm -f ${PROGS} ${TEMPFILES} file.hole
