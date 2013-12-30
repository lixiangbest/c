#ifeq usage
libs=-lgnu
nor_libs=-nor
CC=gcc

#ifdef
bar1=
foo1=($bar1)
ifdef foo1
	forbozz=yes
else
	forbozz=no
endif

foo2=
ifdef foo2
	forbozz1=yes
else
	forbozz1=no
endif

all:
	@echo $(forbozz)
	@echo $(forbozz1)

ifeq ($(CC),gcc)
	@echo $(libs)
else
	@echo $(nor_libs)
endif

ifeq '$(CC)' 'gcc'
	@echo $(nor_libs)
else
	@echo $(libs)
endif

ifeq '$(CC)' "gcc"
	@echo $(nor_libs)
else
	@echo $(libs)
endif
#variable is empty.
ifeq ($(strip $(foo)),)
	@echo foo empty
else
	@echo foo noempty
endif

ifneq "$(CC)" 'gcc'
	@echo not gcc
else
	@echo gcc
endif
