#include	"unp.h"

/* TCP daytime 客户端：连接指定 IP 的 13 号端口，并打印服务器返回的时间字符串。 */
int
main(int argc, char **argv)
{
	/* 保存套接字描述符、读取到的字节数、接收缓冲区和服务器地址。 */
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	/* 检查命令行参数，程序需要一个服务器 IP 地址。 */
	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	/* 创建一个 IPv4 TCP 套接字，用于和 daytime 服务器建立连接。 */
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	/* 初始化服务器地址结构，并设置协议族和 daytime 服务端口 13。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13);	/* daytime server */

	/* 将命令行传入的点分十进制 IP 地址转换成网络字节序的二进制地址。 */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	/* 连接到服务器，连接成功后服务器会发送当前时间字符串。 */
	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	/* 循环读取服务器发来的数据，添加字符串结束符后输出到标准输出。 */
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}

	/* 如果 read 返回负数，说明读取过程中发生错误。 */
	if (n < 0)
		err_sys("read error");

	/* 正常结束客户端程序。 */
	exit(0);
}

/*
 * 作用：
 *   TCP daytime 客户端，连接指定服务器的 13 号端口并显示服务器返回的时间。
 *
 * 工作流程：
 *   1. 从命令行读取服务器 IP 地址。
 *   2. 创建 IPv4 TCP 套接字。
 *   3. 设置服务器地址结构，包括 IP 地址和 13 号端口。
 *   4. 调用 connect 连接服务器。
 *   5. 循环读取服务器发送的时间字符串，并输出到标准输出。
 *   6. 如果读取出错则报错，否则正常退出。
 */
