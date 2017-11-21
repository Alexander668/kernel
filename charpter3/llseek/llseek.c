/*************************************************************************
	> File Name: llseek.c
	> Function: 
	> Author: alex
	> Mail:1072450940@qq.com 
	> Created Time: 2017年11月20日 星期一 21时50分45秒
	> Version: v1.0
 ************************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

static struct  cdev cdev;
static dev_t dev_number = 0;
static int major = 0;
static int minor = 0;
static int dev_sum = 10;

module_param(major, int , S_IRUGO);
module_param(dev_sum , int , S_IRUGO);

static bool is_register_ok = false;


static int this_open(struct inode * inodp, struct file * filp)
{
	printk("in function : %s\n",__func__);
	printk("		open ok \n");
	printk("		and it's offset is %lld\n",filp->f_pos);
	return 0;
}

static int this_close(struct inode * inodp, struct file * filp)
{
	printk("in function : %s\n",__func__);
	printk("		close ok \n");
	printk("		and it's offset is %lld\n",filp->f_pos);
	return 0;
}

static ssize_t 
this_read(struct file *filp, char __user * buff, 
		size_t size , loff_t *offset)
{
	printk("in function : %s\n",__func__);
	printk("		offset : %lld\n",*offset);
	printk("		size : %lu\n",size);
	printk("		pos : %lld\n",filp->f_pos);
	
	filp->f_op->llseek(filp,size,1);
	return size;
}


static loff_t 
this_llseek(struct file * filp, loff_t offset , int number)
{
	loff_t cur_offset;
	printk("in function : %s\n",__func__);
	printk("before llseek : ");
	printk("		pos: %lld\n",filp->f_pos);
	printk("		offset : %lld\n",offset);
	printk("		number : %d\n",number);
	
	switch(number){
		case 0:
			cur_offset = offset;
			break;
		case 1:
			cur_offset = filp->f_pos + offset;
			break;
		case 2:
			cur_offset = 0 + offset;
			break;
		default:
			return -EINVAL;
	}
	if(cur_offset < 0){
		cur_offset = 0;
	}
	
	filp->f_pos = cur_offset;
	printk("after llseek : \n");
	printk("		pos: %lld\n",filp->f_pos);
	printk("		offset : %lld\n",offset);
	printk("		number : %d\n",number);
	return cur_offset;
}
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = this_open,
	.release = this_close,
	.llseek = this_llseek,
	.read = this_read
};

static inline void __exit
llseek_exit(void)
{
	if(is_register_ok){
		cdev_del(&cdev);
		unregister_chrdev_region(dev_number,10);
	}
}

static inline int __init
llseek_init(void)
{
	int ret = 0;
	int i = 0;

	if(major == 0){
		ret = alloc_chrdev_region(&dev_number,0,10,"llseek test");
	}	
	else {
		dev_number = MKDEV(major,minor);
		ret = register_chrdev_region(dev_number,10,"llseek test");
	}
	
	if(ret){
		printk("register or alloc char device failed\n");
		return ret;
	}
	else {
		major = MAJOR(dev_number);
		is_register_ok = true;
	}

	cdev_init(&cdev,&fops);
	
	for(i = 0;i < dev_sum;i++){
		ret = cdev_add(&cdev, dev_number + i,1);
		if(ret){
			goto cdev_add_failed;
		}
	}
	
	return 0;

cdev_add_failed:
	cdev_del(&cdev);
	is_register_ok = false;
	return ret;
}


module_init(llseek_init);
module_exit(llseek_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex, 1072450940@qq.com");
