/*************************************************************************
	> File Name: module_param.c
	> Function: 
	> Author: alex
	> Mail:1072450940@qq.com 
	> Created Time: 2017年11月13日 星期一 20时04分34秒
	> Version: v1.0
 ************************************************************************/
#include <linux/module.h>
#include <linux/init.h>

static int param = 0;

module_param(param , int , S_IRUGO);


static inline void __exit module_param_exit(void)
{
	printk("this is exit , param value : %d\n",param);
}


static inline int __init module_param_init(void)
{
	printk("this is init param value : %d\n",param);	
	return 0;
}


module_init(module_param_init);


module_exit(module_param_exit);

MODULE_LICENSE("GPL");
