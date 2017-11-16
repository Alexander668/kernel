/*************************************************************************
	> File Name: module_param_array.c
	> Function: 
	> Author: alex
	> Mail:1072450940@qq.com 
	> Created Time: 2017年11月13日 星期一 20时21分10秒
	> Version: v1.0
 ************************************************************************/
#include <linux/module.h>
#include <linux/init.h>

static unsigned int circle_times = 10;
module_param(circle_times, uint , S_IRUGO);

static int array_size = 100;
static int array[100] = {0};

module_param_array(array,int , &array_size,S_IRUGO);

	static inline void __exit
module_param_array_exit(void)
{
	int i;

	printk("this is exit\n");

	for(i = 0;i < circle_times ; i++)
	{
		printk("%d : %d\n",i, array[i]);
	}
	
}



	static inline int __init 
module_param_array_init(void)
{
	int  i;
	printk("this is init\n");
	printk("%d\n",(circle_times > 100)? 100: circle_times);
	circle_times = (circle_times > 100) ? 100 : circle_times;
	for(i = 0;i < circle_times ; i++)
	{
		printk("%d : %d\n",i, array[i]);
	}
	
	return 0;
}


module_init(module_param_array_init);

module_exit(module_param_array_exit);

MODULE_LICENSE("GPL");
