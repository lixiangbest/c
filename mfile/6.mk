objs=main.o cmd.o
VPATH=./inc
.LOW_RESOLUTION_TIME:all
all:$(objs)
	gcc -o 6 -g $(objs)

$(objs):defs.h

main.o:fun.h

.PHONY:clean
clean:
	-rm -f 6 $(objs)
