DIRS=lib 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15\
	 16 17 18 19
all:
	$(MAKE) `./systype.sh`

clean:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE) -f `../systype.sh`.mk clean) || exit 1; \
	done

freebsd:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE) -f freebsd.mk) || exit 1; \
	done

linux:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE) -f linux.mk) || exit 1; \
	done

solaris:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE) -f solaris.mk) || exit 1; \
	done

