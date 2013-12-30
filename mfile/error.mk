# include the common file for make command.
# '-' will ignore the input error.
-include define
# error make command
# no such file or directory.
obj=err.o
all:$(obj)
	gcc -o err $(obj)

err.o:defs.h

.PHONY=clean
clean:
	-rm err $(obj)
