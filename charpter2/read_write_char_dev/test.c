/*************************************************************************
	> File Name: test.c
	> Function: 
	> Author: alex
	> Mail:1072450940@qq.com 
	> Created Time: 2017年11月21日 星期二 22时57分27秒
	> Version: v1.0
 ************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	int fd = open("test",O_RDWR);
	char buff1[128] = "alex";
	char buff2[128] = {0};
	if(fd < 0){
		perror("read error");
		return -1;
	}

	write(fd,buff1,128);
	lseek(fd, -128,SEEK_CUR);	
	read(fd,buff2,128);	
	
	printf("%s\n",buff2);
	return 0;
}
