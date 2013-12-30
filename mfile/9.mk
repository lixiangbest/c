a_dirs:=dira dirb
1_dirs:=dir1 dir2

a_files:=filea fileb
1_files:=file1 file2

ifeq "$(use_a)" "yes"
	a1:=a
else
	a1:=1
endif


ifeq "$(use_dirs)" "yes"
	df:=dirs
else
	df:=files
endif

dirs:=$($(a1)_$(df))

a1:=a
a_objects:=a.o b.o c.o
1_objects:=1.o 2.o 3.o
sources:=$($(a1)_objects:.o=.c)

#use condition and sort
ifndef do_sort
	func:=sort
else
	func:=strip
endif

bar1:=a d b g q c
foo1:=$($(func) $(bar1))

objs=main.o foo.o bar.o utils.o
objs+=another.o

all:
	@echo $(dirs)
	@echo $(sources)
	@echo $(func)
	@echo $(bar1)
	@echo $(foo1)
	@echo $(objs)
