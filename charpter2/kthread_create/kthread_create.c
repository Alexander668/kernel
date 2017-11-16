/*************************************************************************
	> File Name: kthread_create.c
	> Function: 
	> Author: alex
	> Mail:1072450940@qq.com 
	> Created Time: 2017年11月16日 星期四 19时13分26秒
	> Version: v1.0
 ************************************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kthread.h>
static struct task_struct * pkthread;

static inline int kthread_func(void * data)
{
	printk("pdata : %p , data : %d\n",data, *((int *)data));

	return 0;
}


static inline void __exit
exit_kthread_stop(void)
{
	if(pkthread->state == TASK_RUNNING){
		kthread_stop(pkthread);
	}
}

static inline int __init
init_kthread_create(void)
{
	int data = 100;
	
	printk("init pdata : %p\n",&data);
	printk("init data : %d\n",data);	
	pkthread = kthread_run(kthread_func, (&data), "alex");
	printk("init data : %d\n",data);	
	
	return 0;
}


module_init(init_kthread_create);
module_exit(exit_kthread_stop);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex , 1072450940@qq.com");
