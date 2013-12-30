include ../Make.defines.linux

PROGS=01_orphan 02_fsess 03_fsess

all:${PROGS}

clean:
	rm -f ${PROGS}
