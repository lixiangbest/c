MODULE_NAME := kernel
obj-m := $(MODULE_NAME).o
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o user user.c
clean:
	rm -fr *.ko *.o *.cmd sender $(MODULE_NAME).mod.c
