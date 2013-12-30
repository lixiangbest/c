include ../Make.defines.linux

PROGS=01_doatexit 02_echoarg 03_cmd 04_cmd 05_testjmp\
	  06_opendata 07_getrlimit

all:${PROGS}

clean:
	rm -f ${PROGS} ${TEMPFILES} file.hole
