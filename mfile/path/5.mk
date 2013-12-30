#sample Makefile
objs = test.o
CFLAGS:=-Wall

%x:CFLAGS+=-g
%.o:CFLAGS+=-O2

%.o %.x:%.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	$(RM) test.o
