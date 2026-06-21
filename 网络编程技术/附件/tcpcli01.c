#include	"unp.h"

/* TCP 回显客户端：连接指定服务器后进入交互式回显流程。 */
int
main(int argc, char **argv)
{
	/* 保存套接字和服务器地址结构。 */
	int					sockfd;
	struct sockaddr_in	servaddr;

	/* 检查命令行参数，需要服务器 IP 地址。 */
	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");

	/* 创建 IPv4 TCP 套接字。 */
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	/* 设置服务器地址和服务端口。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	/* 连接 TCP 服务器。 */
	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	/* 调用客户端交互函数处理标准输入和服务器回复。 */
	str_cli(stdin, sockfd);		/* do it all */

	/* 正常退出程序。 */
	exit(0);
}

/*
 * 作用：
 *   TCP 回显客户端入口程序，连接指定 IP 的服务器并启动交互式回显。
 *
 * 工作流程：
 *   1. 从命令行读取服务器 IP 地址。
 *   2. 创建 IPv4 TCP 套接字。
 *   3. 设置服务器地址结构和端口。
 *   4. 调用 Connect 建立 TCP 连接。
 *   5. 调用 str_cli 处理用户输入和服务器回显。
 *   6. 交互结束后退出程序。
 */
