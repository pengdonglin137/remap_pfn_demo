ifneq ($(KERNELRELEASE),)
	obj-m := regmap_pfn_kmalloc.o
	obj-m += regmap_pfn_vmalloc.o
	obj-m += regmap_pfn_alloc_pages.o
else
	PWD := $(shell pwd)
	KERNELDIR ?= $(PWD)/../../linux-4.10.17
default:
	$(MAKE) -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- M=$(PWD) modules
	cp *.ko /nfsroot

clean:
	@rm -rf *.o *.mod.c *.mod.o *.ko *.order *.symvers .*.cmd .tmp_versions
endif
