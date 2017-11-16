/*************************************************************************
  > File Name: printk_maintask.c
  > Function: 
  > Author: alex
  > Mail:1072450940@qq.com 
  > Created Time: 2017年11月15日 星期三 19时25分27秒
  > Version: v1.0
 ************************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
//#include <linux/init_task.h>

	static inline void __exit
printk_inittask_exit(void)
{
	struct task_struct * ptask;
	
	for(ptask = current ; ptask != &init_task ; ptask = ptask->parent){
		printk("pid : %d , comm : %s \n",ptask->pid , ptask->comm);
	}

}

	static inline int __init
printk_inittask_init(void)
{
	struct task_struct * ptask;
	
	ptask = current;

	for_each_process(ptask){
		printk("pid : %d , common : %s\n",ptask->pid , ptask->comm);
	}
	
	return 0;
}

module_init(printk_inittask_init);
module_exit(printk_inittask_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex 1072450940@qq.com");
