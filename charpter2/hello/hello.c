/*************************************************************************
	> File Name: hello.c
	> Function: 
	> Author: alex
	> Mail:1072450940@qq.com 
	> Created Time: 2017年11月12日 星期日 15时03分31秒
	> Version: v1.0
 ************************************************************************/
#include <linux/module.h>
#include <linux/init.h>


static inline void __exit hello_exit(void)
{
	printk("this is hello module\n");
}

static inline int __init 
hello_init(void)
{
	printk("this is hello module\n");
	return 0;
}


module_init(hello_init);
module_exit(hello_exit);
