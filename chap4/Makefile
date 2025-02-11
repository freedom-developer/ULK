PWD := $(shell pwd)
KVER := $(shell uname -r)
KDIR := /lib/modules/$(KVER)/build

obj-m := demo.o
demo-objs := demo.o ../common/common.o

ccflags-y := -I$(PWD)/../common

all:
	$(MAKE) -C $(KDIR) M=$(PWD)

clean:
	$(RM) -rf .tmp_versions .*.mk .*.cmd *.ko *.mod.c *.o *.symvers *.order *-safe ../common/*.o ../common/.*.o.cmd
