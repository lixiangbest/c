# test makefile
# usage make -f 11.mk debug
# usage make -f 11.mk -e debug
# usage make -f 11.mk -e HOSTNAME=server-ftp
HOSTNAME = server-http
.PHONY:debug
debug:
	@echo "hostname is:$(HOSTNAME)"
	@echo "shell is $(SHELL)"
