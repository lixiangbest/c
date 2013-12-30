#usage: make -f 1.mk
#sample Makefile
#more often use and common use.
cc = gcc
objects=main.o cmd.o

#the final object.
all:$(objects)
	$(cc) -o 2 $(objects)

#defs.h is the prerequisites of all of the objects.
$(objects):defs.h

#funs.h is the only prerequisites of main.o.
main.o:funs.h

.PHONY:clean
clean:
	rm 2 $(objects)
