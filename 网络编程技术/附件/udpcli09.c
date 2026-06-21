#include	"unp.h"

/* UDP 客户端示例：connect 后查看内核分配的本地地址。 */
int
main(int argc, char **argv)
{
	/* 保存 UDP 套接字、地址长度、本地地址和服务器地址。 */
	int					sockfd;
	socklen_t			len;
	struct sockaddr_in	cliaddr, servaddr;

	/* 检查命令行参数，需要服务器 IP 地址。 */
	if (argc != 2)
		err_quit("usage: udpcli <IPaddress>");

	/* 创建 IPv4 UDP 套接字。 */
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	/* 设置服务器地址和端口。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	/* connect UDP 套接字，让内核选择本地地址和端口。 */
	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	/* 获取并打印本地套接字地址。 */
	len = sizeof(cliaddr);
	Getsockname(sockfd, (SA *) &cliaddr, &len);
	printf("local address %s\n", Sock_ntop((SA *) &cliaddr, len));

	/* 正常退出程序。 */
	exit(0);
}

/*
 * 作用：
 *   演示 UDP 套接字调用 connect 后，如何查看内核自动分配的本地地址。
 *
 * 工作流程：
 *   1. 从命令行读取服务器 IP 地址。
 *   2. 创建 UDP 套接字并设置服务器地址。
 *   3. 对 UDP 套接字调用 Connect。
 *   4. 使用 Getsockname 获取本地 IP 和端口。
 *   5. 打印本地地址后退出。
 */
