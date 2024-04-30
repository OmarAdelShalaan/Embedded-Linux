obj-m += alloc_chrdev_region.o  # Specify the module name correctly

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules  # Use $(shell ...) instead of ${shell ...} for command substitution
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean  # Use $(shell ...) instead of ${shell ...} for command substitution
