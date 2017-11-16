/*************************************************************************
	> File Name: module_param_charp.c
	> Function: 
	> Author: alex
	> Mail:1072450940@qq.com 
	> Created Time: 2017年11月13日 星期一 20时13分25秒
	> Version: v1.0
 ************************************************************************/
#include <linux/module.h>
#include <linux/init.h>


char * pointer = "hello world";

module_param(pointer , charp, S_IRUGO);


static inline void __exit
module_param_charp_exit(void)
{
	printk("module param charp exit : %s\n",pointer);
}

static inline int __init
module_param_charp_init(void)
{
	printk("module param charp : %s\n",pointer);
	
	return 0;
}


module_init(module_param_charp_init);

module_exit(module_param_charp_exit);


MODULE_LICENSE("GPL");

