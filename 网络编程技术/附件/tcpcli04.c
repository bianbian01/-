#include	"unp.h"

/* TCP 回显客户端：同时建立 5 个连接，使用第一个连接进行交互。 */
int
main(int argc, char **argv)
{
	/* 保存循环变量、5 个套接字和服务器地址。 */
	int					i, sockfd[5];
	struct sockaddr_in	servaddr;

	/* 检查命令行参数，需要服务器 IP 地址。 */
	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");

	/* 创建 5 个到同一服务器的 TCP 连接。 */
	for (i = 0; i < 5; i++) {
		/* 为当前连接创建 TCP 套接字。 */
		sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);

		/* 设置服务器地址和端口。 */
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);
		Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

		/* 连接服务器。 */
		Connect(sockfd[i], (SA *) &servaddr, sizeof(servaddr));
	}

	/* 使用第一个连接进行标准输入和服务器回显交互。 */
	str_cli(stdin, sockfd[0]);		/* do it all */

	/* 正常退出程序。 */
	exit(0);
}

/*
 * 作用：
 *   TCP 回显客户端示例，一次创建多个 TCP 连接，并使用其中一个连接进行交互。
 *
 * 工作流程：
 *   1. 从命令行读取服务器 IP 地址。
 *   2. 循环创建 5 个 TCP 套接字。
 *   3. 每个套接字都连接到同一个服务器地址和端口。
 *   4. 使用第一个连接调用 str_cli 进行回显交互。
 *   5. 交互结束后退出程序。
 */
