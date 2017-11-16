/*************************************************************************
	> File Name: current.c
	> Function: 
	> Author: alex
	> Mail:1072450940@qq.com 
	> Created Time: 2017年11月15日 星期三 19时10分14秒
	> Version: v1.0
 ************************************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <asm/current.h>

static inline void __exit
current_exit(void)
{
	printk("current pid : %d , current common : %s\n",current->pid, current->comm);
}

static inline int __init
current_init(void)
{
	printk("current pid : %d , current common : %s\n",current->pid, current->comm);
	return 0;
}

module_init(current_init);
module_exit(current_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex 1072450940@qq.com");
