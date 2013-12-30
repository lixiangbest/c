#define  variable.
#recursive replace variable.
foo=$(bar)
bar = $(ugh)
ugh = Huh?

x=foo
y=$(x) bar
x=later

m= foo
# := use value replace other variable,
# can not quote variable defined below.
n:=$(m) bar
m=later

# use shell command and function
ifeq (0,${MAKELEVEL})
	cur_dir:=$(shell pwd)
	whoami:=$(shell whoami)
	host-type:=$(shell arch)
	MAKE:=${MAKE} cur_dir=${cur_dir}  host-type=${host-type} whoami=${whoami}
endif

# use space.
nullstring:=
space:= $(nullstring) #end of the line;comment has space before.
s:= lixiang$(space)lixiang

all:;echo $(foo)
	@echo $(x)
	@echo ${y}
	@echo $(m)
	@echo $(n)
	@echo ${MAKE}
	@echo $(space)
	@echo $(s)
