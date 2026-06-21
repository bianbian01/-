#include	"unp.h"
#include	<time.h>

/* TCP daytime 服务器：监听 13 号端口，客户端连接后返回当前时间。 */
int
main(int argc, char **argv)
{
	/* 保存监听套接字、已连接套接字、服务器地址、发送缓冲区和当前时间。 */
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;

	/* 创建一个 IPv4 TCP 监听套接字。 */
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	/* 初始化服务器地址结构，绑定到本机所有网卡的 13 号 daytime 端口。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(13);	/* daytime server */

	/* 将监听套接字绑定到上面设置的服务器地址。 */
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	/* 开始监听客户端连接请求，LISTENQ 表示等待连接队列长度。 */
	Listen(listenfd, LISTENQ);

	/* 服务器持续运行：接受连接、发送当前时间、关闭本次连接。 */
	for ( ; ; ) {
		/* 阻塞等待客户端连接，连接成功后返回已连接套接字。 */
		connfd = Accept(listenfd, (SA *) NULL, NULL);

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
 *   TCP daytime 服务器，监听 13 号端口，为连接进来的客户端返回当前系统时间。
 *
 * 工作流程：
 *   1. 创建 IPv4 TCP 监听套接字。
 *   2. 将套接字绑定到本机所有网卡的 13 号端口。
 *   3. 调用 listen 进入监听状态。
 *   4. 在无限循环中等待客户端连接。
 *   5. 每接受一个连接，就获取当前时间并格式化成字符串。
 *   6. 把时间字符串写给客户端，然后关闭本次连接。
 */
