#sample Makefile
#use make -f 2.mk CFLAGS=-02
#use make -f 2.mk CFLAGS=-02 debug
EXEF=main
override CFLAGS+=-Wall -g

.PHONY:all cmd
all:$(EXEF) cmd
cmd:cmd.c
$(EXEF):funs.h defs.h
	$(CC) $(CFLAGS) $(addsuffix .c,$@) -o $@
debug:
	@echo "CFLAGS = $(CFLAGS)"

