include ./Make.defines

#Those include Makefile
DIRS = lib libfree test 01 03 04 05 06 07 08\
	   10 11 13 14 15 16 17 18 19\
	   pcap thread
OS = linux

all:
	@echo "Nothing to make in this directory"
	@echo "Please read the READE file"
	@echo "Cleanfiles:" $(CLEANFILES)
	@echo "cc:" $(CC) ";cpp:" $(CPP)
	@echo "cflags:" $(CFLAGS) ";arflags:" $(ARFLAGS)
	@echo "ldlibs:" $(LDLIBS) ";ld:" $(LD) "dld:" $(DLD)
	@echo "libs_xti:" $(LIBS_XTI) ";ranlib:" $(RANLIB)
	@echo "compile.c:" $(COMPILE.C) ";LINK.c:" $(LINK.c)
	@echo "libunp_name:" $(LIBUNP_NAME)
	@echo "libunpxti_name:" $(LIBUNPXTI_NAME)
	@echo "rm:" $(RM) ";ar:" $(AR) ";extralibs:" $(EXTRALIBS)
	@echo "ccflags:" $(CCFLAGS) ";makeinfo:" $(MAKEINFO)
	@echo "incldirs:" $(INCLDIRS) ";makeflags:" $(MAKEFLAGS)
	@echo "\nstart compile:"
	$(MAKE) $(OS)

#each dir must make.
linux:
	for i in $(DIRS); do\
		(cd $$i && $(MAKE)) || exit 1;\
	done

clean:
	rm -f $(CLEANFILES)

distclean:
	rm -f $(CLEANFILES) config.cache config.log\
	config.status config.h Make.defines Makefile
