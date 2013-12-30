#fetch variable value
deferred = me
Immediate=deferred
Immediate1?=$(deferred)
Immediate2:=$(deferred)
Immediate+=deferred or $(Immediate2)
define Immediate3
	Immediate
endef
all:
	@echo $(Immediate)
	@echo $(Immediate1)
	@echo $(Immediate2)
	echo $(Immediate3)

