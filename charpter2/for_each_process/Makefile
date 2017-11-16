obj-n		:=for_each_process
obj-m		:= $(obj-n).o
kernel		:= /lib/modules/`uname -r`/build/

all:
		make -C $(kernel) M=$(shell pwd) modules
clean:
		make -C $(kernel) M=$(shell pwd) clean
