Path=/home
do:
	@echo $Path
	@echo ${Path}
	@echo $(Path)

.PHONY:cleanall cleanobj
cleanall:cleanobj
	touch program
	rm program
cleanobj:
	$(RM) *.o
