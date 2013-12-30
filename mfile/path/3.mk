#makefile default rules.
CUR_DIR=$(shell pwd)
INCS:=$(CUR_DIR)/src
CFLAGS:=-Wall -I$(INCS)

EXEF:=foo

.PHONY:all clean
all:$(EXEF)
	@echo $(PC)
	@echo $(ARFLAGS)
	
foo:CFLAGS+=-O2

.PHONY:clean
clean:
	$(RM) foo
	@echo $(dg)
#run $ make -f 3.mk dg=m
