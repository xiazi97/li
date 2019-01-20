1.

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

void copy_file(char* srcfile ,char* desfile)
{
	int src_fd = open(srcfile,O_RDONLY,0666);
	int des_fd = open(desfile,O_CREAT | O_TRUNC | O_WRONLY);
	char buf[1024];
	int nBits;
	int write_ret;

	while(nBits = read(src_fd,buf,100))
	{
		write_ret = write(des_fd,buf,nBits);
		if(write_ret < 0)
		{
			perror("Write error!");
			exit(1);
		}
	}
	close(src_fd);
	close(des_fd);
}

void hanbook()
{
	printf("usage: ./cp [filename1] [filename2]\n");
}

int main(int argc ,char** argv)
{
	if(argc != 3)
	{
		handbook();
		return;
	}
	copy_file(argv[1],argv[2]);
	return 0
}