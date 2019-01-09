#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>

#define BUF_SIZE 20
#define IP "192.168.72.131"
#define SPORT 10086

int main()
{
	int i;
	int sock = 0;
	int ret = 0;
	struct sockaddr_in serverAddr;
	int addrLenth = sizeof(struct sockaddr_in);
	char  buf[][5] = {{0xff,0x00,0x01,0x00,0xff},
					{0xff,0x00,0x02,0x00,0xff},
					{0xff,0x00,0x03,0x00,0xff},
					{0xff,0x00,0x04,0x00,0xff},
					{0xff,0x00,0x00,0x00,0xff}};

	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket error");
		return -1;
	}

	memset(&serverAddr,0,addrLenth);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SPORT);
	serverAddr.sin_addr.s_addr = inet_addr(IP);

	ret = connect(sock,(struct sockaddr_in*)&serverAddr,addrLenth);

	if(ret < 0)
	{
		perror("Connect error!!");
		close(sock);
		return -1;
	}
	while(1)
	{

	printf("Client#");
	scanf("%d",&i);
	switch(i)
	{
	case 1:
		printf("bbb");
			ret = send(sock,buf[0],5,0);
			//ret = write(sock,buf[0],6);
		break;
	case 2:
		ret = write(sock,buf[1][5],BUF_SIZE);
		break;
	case 3:
		ret = write(sock,buf[2][5],BUF_SIZE);
		break;
	case 4:
		ret = write(sock,buf[3][5],BUF_SIZE);
		break;
	case 5:
		ret = write(sock,buf[4][5],BUF_SIZE);
		break;
	
	}
	printf("aaa");
	if(ret > 0)
	{
		printf("send message success!\r\n");
	}
	}
//	close(sock);
}
