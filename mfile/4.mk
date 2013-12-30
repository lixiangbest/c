#usage: make -f 1.mk
#sample Makefile
#more often use and common use.
cc = gcc
objects=main.o cmd.o 

#the final object.
all:$(objects);$(cc) -o 4 $(CFLAGS) $(objects)
	@echo $(CFLAGS)parameter

#defs.h is the prerequisites of all of the objects.
$(objects):defs.h

#funs.h is the only prerequisites of main.o.
main.o:funs.h

#"make print" echo the last updated '.c' files.
print:*.c
	lpr -p $?
	touch print

.PHONY:clean
clean:
	rm 4 $(objects)
