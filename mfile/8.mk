foo := home
#if foo not define,then define foo=bar
foo?=bar

#equal to blow
ifeq ($(origin fm),undefined)
	fm = bar
endif

#variable replace
fd:=a.o b.o c.o
ba:=$(fd:.o=.c)

#same function
fdm:=a.o b.o c.o
bam:=$(fdm:%.o=%.c)

#variable recursive use
x=y
y=z
a:=$($(x))

#variable usage
x1=var1
var2:=Hello
y1=$(subst 1,2,$(x1))
z1=y1
a1:=$($($(z1)))

all:
	@echo $(foo)
	@echo $(fm)
	@echo $(fd)
	@echo $(ba)
	@echo $(fdm)
	@echo $(bam)
	@echo $(a)
	@echo $(a1)
