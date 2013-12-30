LIBS=libtest.a
GPATH=src
VPATH=src
LDFLAGS+=-L ./. -ltest

libtest.a:sum.o memcp.o
	$(AR) $(ARFLAGS) $@ $^
	@echo $@
	@echo $^

.PHONY:clean
clean:
	-rm -f $(LIBS) *.o
