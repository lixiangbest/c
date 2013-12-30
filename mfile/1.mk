#include common files for make command.
-include defines
#usage: make -f 1.mk
#sample Makefile
#more often use and common use.
cc = gcc
objects=main.o cmd.o

#the final object.
all:$(objects)
	@echo cc=$(cc)
	@echo obj=$(objects)
	@echo inc=$(MAKEFILE_LIST)
	$(cc) -o 1 $(objects)

#main.o use the default execute rule.
main.o:funs.h defs.h

#cmd.o use the default execute rule.
cmd.o:defs.h

#usage: make -f 1.mk clean
#if there is 'clean' file in the same directory,
#it also clean all of objects.
#.PHONY is the key.
#'-' ignore the rm command error.
.PHONY:clean
clean:
	-rm 1 $(objects)
