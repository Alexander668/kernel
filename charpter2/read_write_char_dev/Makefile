obj-n		:= read_and_write_char_dev
obj-m		:= $(obj-n).o

kernel		:= /lib/modules/`uname -r`/build/

all:
		make -C $(kernel) M=$(shell pwd) modules
clean:
		make -C $(kernel) M=$(shell pwd) clean
