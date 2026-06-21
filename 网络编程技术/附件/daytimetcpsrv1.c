#include	"unp.h"
#include	<time.h>

/* TCP daytime 服务器：监听 13 号端口，打印客户端地址并返回当前时间。 */
int
main(int argc, char **argv)
{
	/* 保存监听套接字、已连接套接字、客户端地址长度、地址结构、缓冲区和当前时间。 */
	int					listenfd, connfd;
	socklen_t			len;
	struct sockaddr_in	servaddr, cliaddr;
	char				buff[MAXLINE];
	time_t				ticks;

	/* 创建一个 IPv4 TCP 监听套接字。 */
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	/* 初始化服务器地址结构，绑定到本机所有网卡的 13 号 daytime 端口。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(13);	/* daytime server */

	/* 将监听套接字绑定到服务器地址。 */
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	/* 开始监听客户端连接请求。 */
	Listen(listenfd, LISTENQ);

	/* 服务器持续运行：接受连接、打印客户端信息、发送当前时间、关闭连接。 */
	for ( ; ; ) {
		/* 初始化客户端地址结构长度，供 Accept 写入客户端地址信息。 */
		len = sizeof(cliaddr);

		/* 阻塞等待客户端连接，并保存客户端 IP 地址和端口号。 */
		connfd = Accept(listenfd, (SA *) &cliaddr, &len);

		/* 将客户端 IP 转换成字符串，并打印客户端 IP 和端口号。 */
		printf("connection from %s, port %d\n",
			   Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
			   ntohs(cliaddr.sin_port));

		/* 获取当前系统时间，并格式化成 daytime 协议返回的字符串。 */
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

		/* 将时间字符串发送给客户端。 */
        Write(connfd, buff, strlen(buff));

		/* 关闭本次客户端连接，继续等待下一个客户端。 */
		Close(connfd);
	}
}

/*
 * 作用：
 *   TCP daytime 服务器，监听 13 号端口，为客户端返回当前系统时间，并打印客户端来源地址。
 *
 * 工作流程：
 *   1. 创建 IPv4 TCP 监听套接字。
 *   2. 将套接字绑定到本机所有网卡的 13 号端口。
 *   3. 调用 listen 进入监听状态。
 *   4. 在无限循环中等待客户端连接，并通过 Accept 获取客户端地址。
 *   5. 打印客户端 IP 地址和端口号。
 *   6. 获取当前系统时间，格式化后发送给客户端。
 *   7. 关闭本次连接，然后继续等待下一个客户端。
 */
