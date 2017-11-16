obj-name 		:= module_param
obj-m			:= $(obj-name).o

kernel			:= /lib/modules/`uname -r`/build/

all:
		make -C $(kernel) M=$(shell pwd) modules
clean:
		make -C $(kernel) M=$(shell pwd) clean
install:
	insmod $(obj-name).ko
