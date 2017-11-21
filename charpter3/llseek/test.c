/*************************************************************************
	> File Name: test.c
	> Function: 
	> Author: alex
	> Mail:1072450940@qq.com 
	> Created Time: 2017年11月20日 星期一 22时13分23秒
	> Version: v1.0
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	int fd = open("test",O_RDWR);
	char buff[128];
	
	if(fd < 0){
		perror("open file error: ");
		return -1;
	}

	lseek(fd,128,0);
	lseek(fd, 128,1);
	
	read(fd,buff,128);
	close(fd);

	return 0;
}
