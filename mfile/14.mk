#use make sys function
#function subst usage
comma:= ,
empty:=
#space:= $(empty) $(empty)
space:= $(empty) 
foo:=a b c
bar:=$(subst $(space),$(comma),$(foo))
	
#function patsubst usage
pat= $(patsubst %.c,%.o,x.c.c bar.c)
pat1= $(patsubst %.c,.o,x%.c bar.c)
pat2= $(pat:%.o=%.c)

objects=foo.o bar.o baz.o
objects1:=$(objects)
pat3 = $(objects:.o=.c)
pat4 = $(patsubst %.o,%.c,$(objects1))

#function strip usage
str=    a   b c
lostr= $(strip $(str))

#function findstring usage
fstr1= $(findstring a,a b c)
fstr2 = $(findstring a,b c)

#function filter usage
sources:=foo.c bar.c baz.s ugh.h
filstr= $(filter %.c %.s,$(sources))
unfilstr= $(filter-out %.c %.s,$(sources))

#function sort usage
sort1:=$(sort foo bar lose foo1)
sort2:=$(sort bar lose foo)

#function word usage
wordstr:=$(word 2,foo bar baz)

#function wordlist usage
wlist:=$(wordlist 2,3,do bar baz loss)
wcount:=$(words do bar baz loss)
wlast:=$(word $(words do bar baz loss),do bar baz loss)

#function firstword usage
fword = $(firstword foo bar)

#complex
VPATH=src:../includes
override CFLAGS+=$(patsubst %,-l%,$(subst :, ,$(VPATH)))

do:
	@echo ${bar}
	@echo $(pat)
	@echo $(pat1)
	@echo $(pat2)
	@echo $(pat3)
	@echo $(pat4)
	@echo $(str)
	@echo $(lostr)
	@echo $(fstr1)
	@echo $(fstr2)
	@echo $(sources)
	@echo $(filstr)
	@echo $(unfilstr)
	@echo $(sort1)
	@echo $(sort2)
	@echo $(wordstr)
	@echo $(wlist)
	@echo $(wcount)
	@echo $(wlast)
	@echo $(fword)
	@echo $(CFLAGS)
