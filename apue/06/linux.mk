include ../Make.defines.linux

PROGS=01_getpwnam 02_getspnam 03_getgrnam 04_sysinfo 05_time

all:${PROGS}

clean:
	rm -f ${PROGS} ${TEMPFILES} file.hole
