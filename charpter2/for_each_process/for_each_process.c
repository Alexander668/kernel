/*************************************************************************
	> File Name: for_each_process.c
	> Function: 
	> Author: alex
	> Mail:1072450940@qq.com 
	> Created Time: 2017年11月16日 星期四 19时03分20秒
	> Version: v1.0
 ************************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>



static inline void __exit
exit_list_each_process(void)
{
	struct task_struct * ptask;

	ptask = current;

	for_each_process(ptask){
		printk("task pid : %d , common : %s\n",ptask->pid , ptask->comm);
	}

}


static inline int __init 
init_list_eachprocess(void)
{
	struct task_struct * ptask = NULL;

	ptask = current;

	for(; ptask != &init_task ; ptask = ptask->parent){
		printk("task pid : %d , common : %s\n", ptask->pid , ptask->comm);
	}

	return 0;
}

module_init(init_list_eachprocess);
module_exit(exit_list_each_process);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex 1072450940@qq.com");
