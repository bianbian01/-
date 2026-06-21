/* include fig01 */
#include	"unp.h"
#include	<limits.h>		/* for OPEN_MAX */

/* TCP 回显服务器：使用 poll 同时管理监听套接字和多个客户端连接。 */
int
main(int argc, char **argv)
{
	/* 保存循环变量、套接字、就绪数量、读写长度、缓冲区和地址结构。 */
	int					i, maxi, listenfd, connfd, sockfd;
	int					nready;
	ssize_t				n;
	char				buf[MAXLINE];
	socklen_t			clilen;
	struct pollfd		client[OPEN_MAX];
	struct sockaddr_in	cliaddr, servaddr;

	/* 创建 IPv4 TCP 监听套接字。 */
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	/* 初始化服务器地址，绑定到 SERV_PORT。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	/* 绑定并监听客户端连接。 */
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	/* 将监听套接字放入 poll 数组第 0 项。 */
	client[0].fd = listenfd;
	client[0].events = POLLRDNORM;

	/* 其余数组项标记为未使用。 */
	for (i = 1; i < OPEN_MAX; i++)
		client[i].fd = -1;		/* -1 indicates available entry */
	maxi = 0;					/* max index into client[] array */
/* end fig01 */

/* include fig02 */
	/* 循环调用 poll，处理新连接和已连接客户端数据。 */
	for ( ; ; ) {
		nready = Poll(client, maxi+1, INFTIM);

		/* 监听套接字可读表示有新客户端连接。 */
		if (client[0].revents & POLLRDNORM) {	/* new client connection */
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
#ifdef	NOTDEF
			printf("new client: %s\n", Sock_ntop((SA *) &cliaddr, clilen));
#endif

			/* 在 poll 数组中寻找空闲位置保存新连接。 */
			for (i = 1; i < OPEN_MAX; i++)
				if (client[i].fd < 0) {
					client[i].fd = connfd;	/* save descriptor */
					break;
				}
			if (i == OPEN_MAX)
				err_quit("too many clients");

			/* 监听该客户端的普通可读事件。 */
			client[i].events = POLLRDNORM;
			if (i > maxi)
				maxi = i;				/* max index in client[] array */

			/* 如果没有更多就绪描述符，重新进入 poll。 */
			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}

		/* 检查所有客户端连接是否有数据可读或错误。 */
		for (i = 1; i <= maxi; i++) {	/* check all clients for data */
			if ( (sockfd = client[i].fd) < 0)
				continue;
			if (client[i].revents & (POLLRDNORM | POLLERR)) {
				/* 读取客户端数据。 */
				if ( (n = read(sockfd, buf, MAXLINE)) < 0) {
					if (errno == ECONNRESET) {
							/*4connection reset by client */
#ifdef	NOTDEF
						printf("client[%d] aborted connection\n", i);
#endif
						/* 客户端复位连接时关闭套接字并释放数组项。 */
						Close(sockfd);
						client[i].fd = -1;
					} else
						err_sys("read error");
				} else if (n == 0) {
						/*4connection closed by client */
#ifdef	NOTDEF
					printf("client[%d] closed connection\n", i);
#endif
					/* 客户端正常关闭时关闭套接字并释放数组项。 */
					Close(sockfd);
					client[i].fd = -1;
				} else
					/* 正常读取到数据时原样写回客户端。 */
					Writen(sockfd, buf, n);

				if (--nready <= 0)
					break;				/* no more readable descriptors */
			}
		}
	}
}
/* end fig02 */

/*
 * 作用：
 *   TCP 回显服务器，使用 poll 在单进程中同时处理多个客户端连接。
 *
 * 工作流程：
 *   1. 创建、绑定并监听 TCP 套接字。
 *   2. 将监听套接字和客户端套接字维护在 poll 数组中。
 *   3. poll 返回后，先处理新的客户端连接。
 *   4. 再遍历已连接客户端，读取可读数据。
 *   5. 客户端关闭或复位连接时清理对应数组项。
 *   6. 正常收到数据时原样写回客户端。
 */
