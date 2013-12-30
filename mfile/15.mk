#function dir usage
dirstr = $(dir src/foo.c hacks)

#function notdir usage
notdirstr = $(notdir src/foo.c hacks)

#function suffix usage
suffstr = $(suffix src/foo.c src-1.0/bar.c  hacks)

#function basename usage
basestr = $(basename src/foo.c src-1.0/bar.c  hacks home/suncco/.font.cache-1)

#function addsuffix usage
addsuffstr = $(addsuffix .c,foo bar) 

#function addprefix usage
addprestr = $(addprefix src/,foo bar)

#function join usage
joinstr = $(join a b d,.c .o)

#function wildcard usage
wildstr = $(wildcard *.c)

#function foreach usage
dirs:=.c .mk
filestr = $(foreach dir,$(dirs),$(wildcard *$(dir)))
filestr2 = $(wildcard *.c *.mk)

#when var define, it do not expand.
find_f = $(wildcard *$(dir))
filestr3=$(foreach dir,$(dirs),$(find_f))

#if function
subdir=$(if $(SRC_DIR) $(SRC_DIR),/home/suncco,/home/src)

#call function
reverse=$(2)$(1)
callstr = $(call reverse,a,b)

pathsearch=$(firstword $(wildcard $(addsuffix /$(1),$(subst :, ,$(PATH)))))
LS:=$(call pathsearch,ls)

pm := $(PATH)
pa = $(subst :, ,$(PATH)) 
pd = $(addsuffix /ls,$(subst :, ,$(PATH)))
pc = $(wildcard c)

map=$(foreach a,$(2),$(call $(1),$(a)))
omap=$(call map,origin,omap map MAKE)

getval= $(value pm)
fooval=$PATH

#error function usage
ERR=$(error found an error!define your erro msg)
err:
	@echo $(ERR)
do:
	@echo $(dirstr)
	@echo $(notdirstr)
	@echo $(suffstr)
	@echo $(basestr)
	@echo $(addsuffstr)
	@echo $(addprestr)
	@echo $(joinstr)
	@echo $(wildstr)
	@echo $(filestr)
	@echo 
	@echo $(filestr2)
	@echo 
	@echo $(filestr3)
	@echo $(subdir)
	@echo pm:$(pm) 
	@echo pa:$(pa)
	@echo pd:$(pd)
	@echo pc:$(pc)
	@echo 
	@echo $(PATH) 
	@echo $(callstr)
	@echo $(wildcard /usr/local/sbin/ls)
	@echo $(omap)
	@echo $(getval)
	@echo 
	@echo $(fooval)
	@echo $(value fooval)
	@echo 
	@echo $(origin $(PATH))
	@echo $(origin MAKE)
	@echo $(shell echo *.c)
	@echo
