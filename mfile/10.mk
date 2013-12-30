var:=value
var+=more

var1:=value
var1:=$(var1) more
var2:=$(var1)
override var2:=lixiang
override var3+=lixiang
var3+=lixiang

define two-lines
	echo var
	echo $(var)
endef

t-lines = echo var;echo $(var)
# global variable
CF+=-m

# object variable
all: CF=-g\
	CF+=-m
all:
	@echo $(var)
	@echo $(var1)
	@echo $(var2)
	@echo $(var3)
	@echo varm
	@echo $(two-lines)
	@echo $(t-lines)
	@echo $(CF)

debug:
	@echo $(var)
	@echo $(var1)
	@echo $(var2)
	@echo $(var3)
	@echo varm
	@echo $(two-lines)
	@echo $(t-lines)
	@echo $(CF)
