#include	"unp.h"

/* UDP 回显客户端入口：构造服务器地址后调用 dg_cli 进行交互。 */
int
main(int argc, char **argv)
{
	/* 保存 UDP 套接字和服务器地址。 */
	int					sockfd;
	struct sockaddr_in	servaddr;

	/* 检查命令行参数，需要服务器 IP 地址。 */
	if (argc != 2)
		err_quit("usage: udpcli <IPaddress>");

	/* 设置服务器 IPv4 地址和端口。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	/* 创建 IPv4 UDP 套接字。 */
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	/* 调用 UDP 客户端函数处理标准输入和服务器回复。 */
	dg_cli(stdin, sockfd, (SA *) &servaddr, sizeof(servaddr));

	/* 正常退出程序。 */
	exit(0);
}

/*
 * 作用：
 *   UDP 回显客户端入口程序，连接指定服务器地址并启动 UDP 回显交互。
 *
 * 工作流程：
 *   1. 从命令行读取服务器 IP 地址。
 *   2. 初始化服务器地址结构和端口。
 *   3. 创建 UDP 套接字。
 *   4. 调用 dg_cli 发送标准输入内容并接收服务器回复。
 *   5. 交互结束后退出程序。
 */
