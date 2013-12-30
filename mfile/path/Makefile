#transfer all of the variables to sub makefile.
#.EXPORT_ALL_VARIABLES:
export
SHELL=/bin/bash
unexport objs
#object file and preprequesties file in the different path.
#VPATH=./:../

objs=main.o cmd.o foo.elc

all:$(filter %.o,$(objs))
	gcc $(CFLAGS) $(filter %.o,$(objs)) -o all
	@echo "main makelevel=$(MAKELEVEL)"
	@echo $(SHELL)
	@echo $(MAKEFLAGS)
	@echo $(MAKEFILES)

#$(objs):defs.h
#main.o:funs.h

#$(objs):%.o:%.c
$(filter %.o,$(objs)):%.o:%.c
	gcc  -c $(CFLAGS) $< -o $@
	@echo $(CC)
	@echo $(RM)
	@echo $(MAKE)
	@echo $<
	echo $@

%.d:%.c
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$;\
	sed's,\($*\).o[:]*,\1.o $@:,g' < $@.$$$$ > $@;\
	#rm -f $@.$$$$

#multi-line shell command.
exec:
	cd /home/suncco
	pwd

#sigle shell command.
execn:
	@cd /home/suncco;pwd

#'\' to connect two line as one executed line
execm:
	cd /home/suncco;\
	pwd

#enter 'src' dir and make in the 'src'dir.
subsys:
	@echo "main makelevel=$(MAKELEVEL)"
	cd src && $(MAKE)
	#cd src && make 

.PHONY:clean
clean:
	-rm -f all $(filter %.o,$(objs))

