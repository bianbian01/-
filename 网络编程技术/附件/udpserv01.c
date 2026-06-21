#include	"unp.h"

/* UDP 回显服务器入口：绑定端口后调用 dg_echo 处理数据报。 */
int
main(int argc, char **argv)
{
	/* 保存 UDP 套接字、服务器地址和客户端地址。 */
	int					sockfd;
	struct sockaddr_in	servaddr, cliaddr;

	/* 创建 IPv4 UDP 套接字。 */
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	/* 初始化服务器地址，绑定到本机所有网卡的 SERV_PORT 端口。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	/* 将 UDP 套接字绑定到服务器地址。 */
	Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

	/* 调用 UDP 回显函数，循环接收并返回客户端数据报。 */
	dg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));
}

/*
 * 作用：
 *   UDP 回显服务器入口程序，监听 SERV_PORT 端口并原样返回客户端数据报。
 *
 * 工作流程：
 *   1. 创建 IPv4 UDP 套接字。
 *   2. 初始化服务器地址并绑定到 SERV_PORT。
 *   3. 调用 dg_echo 进入无限循环。
 *   4. dg_echo 接收客户端数据报并原样发送回客户端。
 */
