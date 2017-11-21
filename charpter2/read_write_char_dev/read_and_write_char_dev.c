/*************************************************************************
  > File Name: read_and_write_char_dev.c
  > Function: 
  > Author: alex
  > Mail:1072450940@qq.com 
  > Created Time: 2017年11月21日 星期二 22时05分15秒
  > Version: v1.0
 ************************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

static dev_t dev_number;
static int dev_sum = 10;
static int major = 0;
static int minor = 0;

static bool is_register_ok = false;

module_param(major , int , S_IRUGO);
module_param(dev_sum , int ,S_IRUGO);
static int data_sum = 1000;

struct scull_device{
	struct cdev cdev;
	void * data;
	int sum;
	int cur_pos;
};

static struct scull_device scull_dev;


static int 
scull_open(struct inode * inodp, struct file * filp)
{
	filp->private_data = &(scull_dev.cdev);

	printk("current position is : %lld\n",filp->f_pos);

	return 0;
}

static int scull_close(struct inode * inodp, struct file * filp)
{
	printk("current position is : %lld\n",filp->f_pos);

	return 0;
}

static loff_t 
scull_llseek(struct file * filp, loff_t count,int wherance)
{
	loff_t cur_pos = filp->f_pos;
	struct scull_device * pscull_device;
	
	pscull_device = container_of(filp->private_data,struct scull_device, cdev);
	
	printk("before seek pos : %lld\n",filp->f_pos);
	printk("		pscull_device sum : %d\n",pscull_device->sum);
	
	switch(wherance){
		case SEEK_SET:
			cur_pos = count;
			printk("		seek set: %lld\n",cur_pos);
			break;
		case SEEK_CUR:
			cur_pos += count;
			printk("		seek cur: %lld\n",cur_pos);
			break;
		case SEEK_END:
			cur_pos = pscull_device->sum + count;
			printk("		seek end : %lld\n",cur_pos);
			break;
		default:
			return -EINVAL;
	}
	
	if(cur_pos < 0){
		filp->f_pos = 0;
	}
	else if(cur_pos > pscull_device->sum){
		filp->f_pos = pscull_device->sum;
	}
	else{
		filp->f_pos = cur_pos;
	}

	printk("after llseek cur pos : %lld\n",filp->f_pos);
	return filp->f_pos;
}

static ssize_t 
scull_read(struct file * filp, char __user * buff, 
		size_t count , loff_t * offset)
{
	int read_count = 0;
	struct scull_device * pscull_device ;
	int ret = 0;
	printk("before read pos : %lld\n",filp->f_pos);
	pscull_device = container_of(filp->private_data,struct scull_device, cdev);
	
	if(filp->f_pos + count > pscull_device->sum){
		read_count = pscull_device->sum - filp->f_pos;
	}
	if(read_count <= 0){
		return 0;
	}
	ret = copy_to_user(buff,pscull_device->data + filp->f_pos,read_count);
	if(ret){
		printk("read error\n");
		return ret;
	}	
	printk("buff read : %s\n",buff);	
	filp->f_op->llseek(filp,read_count,SEEK_CUR);
	printk("after read pos : %lld\n",filp->f_pos);
	return read_count;
}

static ssize_t 
scull_write(struct file * filp,const char __user * buff,
		size_t count, loff_t * offset)
{
	int write_count = count;
	struct scull_device *pscull_dev;
	int ret = 0;

	pscull_dev = container_of(filp->private_data, struct scull_device, cdev);
	printk("before write pos : %lld\n",filp->f_pos);
	
	if(filp->f_pos  + count > pscull_dev->sum){
		write_count = pscull_dev->sum - filp->f_pos;
	}
	if(write_count <= 0){
		return write_count;
	}
	
	ret = copy_from_user(pscull_dev->data + filp->f_pos,buff, write_count);
	printk("buff write : %s\n",buff);	
		
	filp->f_op->llseek(filp,write_count , SEEK_CUR);
	
	printk("after write pos : %lld\n",filp->f_pos);
	return write_count;
}



static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = scull_open,
	.release = scull_close,
	.read = scull_read,
	.write = scull_write,
	.llseek = scull_llseek
};

	static inline void __exit
read_and_write_char_dev_exit(void)
{
	if(is_register_ok){
		cdev_del(&(scull_dev.cdev));
		unregister_chrdev_region(dev_number, dev_sum);
		kfree(scull_dev.data);
		printk("quit module %s\n",__FILE__);
	}
}

	static inline int __init
read_and_write_char_dev_init(void)
{
	int ret = 0;
	int i = 0;

	if(major == 0){
		ret = alloc_chrdev_region(&dev_number,0,10,"read_and_write_char_device");	
	}
	else if((major > 0) && (major < 256)) {
		dev_number = MKDEV(major,minor);
		ret = register_chrdev_region(dev_number, 10,"read_and_write_char_device");
	}
	else {
		printk("major is wrong!\n");
		printk("major value is : %d\n",major);
		return -EINVAL;
	}

	if(ret){
		printk("reigster char device region is wrong\n");
		return ret;
	}
	else {
		major = MAJOR(dev_number);
		is_register_ok = true;
		printk("register char device ok , and major is : %d\n",major);
	}

	cdev_init(&(scull_dev.cdev),&fops);
	for(i = 0 ;i < dev_sum;i++){
		ret = cdev_add(&(scull_dev.cdev),dev_number + i,1);
		if(ret){
			goto cdev_add_failed;
		}
	}

	printk("cdev add ok \n");
	scull_dev.sum = data_sum;
	scull_dev.cur_pos = 0;
	scull_dev.data = kmalloc(scull_dev.sum,GFP_KERNEL);
	if(IS_ERR(scull_dev.data)){
		ret = PTR_ERR(scull_dev.data);
		printk("get data failed \n");
		goto cdev_add_failed;
	}
	printk("get data ok , and it's position is : %p\n",scull_dev.data);	

	return 0;

cdev_add_failed:
	cdev_del(&(scull_dev.cdev));
	is_register_ok = false;
	return ret;
}



module_init(read_and_write_char_dev_init);
module_exit(read_and_write_char_dev_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("alex,1072450940@qq.com");
