CC=gcc
# 'edit' is the final executed file.
# 'edit' is the target and this '.o' files behind the 'edit'
# all '.o' files is the prerequisites of 'edit' 
# and is the target of '.c' and '.h'
edit:main.o \
	cmd.o
	$(CC) -o edit main.o cmd.o

# '.c' and '.h' is the prerequisites of 'main.o'
main.o:main.c funs.h defs.h

#$(CC) -c main.c

cmd.o:cmd.c defs.h

#$(CC) -c cmd.c

# 'edit' is the final executed file.
# when there the 'clean' file in the same directory,
# it will make no effect.
clean:
	rm -f edit *.o
#	rm edit main.o cmd.o 
