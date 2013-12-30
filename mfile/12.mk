# sample Makefile
CUR_DIR=$(shell pwd)
INCS:=$(CUR_DIR)/path
CFLAGS:=-Wall -l$(INCS)

EXEF:=main.o cmd.o

.PHONY:all clean
all:$(EXEF)
	$(CC) -o 12 $(EXEF)
$(EXEF):defs.h

main:CFLAGS+=-O2
main:funs.h
	$(CC) $(CFLAGS) -c main.c
cmd:CFLAGS+=-g;$(CC) $(CFLAGS) -c cmd.c

#$(CC) $(CFLAGS) $(addsuffix .c,$@) -c $@

clean:
	$(RM) *.o *.d $(EXEF)

