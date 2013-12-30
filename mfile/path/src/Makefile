define run-yacc
@echo $(firstword $@)
echo $(firstword $^)
endef
ifeq ($(MAKELEVEL),0)
all:msg
	@$(run-yacc)
else
all:other
	$(run-yacc)
endif

msg:
	@echo $(objs)
	echo $(SHELL)
	echo $(MAKE)
	@echo "subdir makelvel=$(MAKELEVEL)"
	@echo "Can not make in this directory!"

other:
	@echo $(objs)
	echo $(SHELL)
	echo $(MAKE)
	@echo "subdir makelvel=$(MAKELEVEL)"
	@echo "Can  make in parent directory!"
