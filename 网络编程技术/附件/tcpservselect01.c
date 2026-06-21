/* include fig01 注意这个程序，课本的第28行少一个“{”*/  
#include	"unp.h"

/* TCP 回显服务器：使用 select 同时管理监听套接字和多个客户端连接。 */
int
main(int argc, char **argv)
{
	/* 保存循环变量、套接字、select 参数、客户端数组、缓冲区和地址结构。 */
	int					i, maxi, maxfd, listenfd, connfd, sockfd;
	int					nready, client[FD_SETSIZE];
	ssize_t				n;
	fd_set				rset, allset;
	char				buf[MAXLINE];
	socklen_t			clilen;
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

	/* 初始化 select 需要的最大描述符和客户端数组。 */
	maxfd = listenfd;			/* initialize */
	maxi = -1;					/* index into client[] array */
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;			/* -1 indicates available entry */
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
/* end fig01 */

/* include fig02 */
	/* 循环调用 select，处理新连接和客户端数据。 */
	for ( ; ; ) {
		rset = allset;		/* structure assignment */
		nready = Select(maxfd+1, &rset, NULL, NULL, NULL);

		/* 监听套接字可读表示有新客户端连接。 */
		if (FD_ISSET(listenfd, &rset)) {	/* new client connection */
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
#ifdef	NOTDEF
			printf("new client: %s, port %d\n",
					Inet_ntop(AF_INET, &cliaddr.sin_addr, 4, NULL),
					ntohs(cliaddr.sin_port));
#endif

			/* 在客户端数组中寻找空位保存新连接。 */
			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i] < 0) {
					client[i] = connfd;	/* save descriptor */
					break;
				}
			if (i == FD_SETSIZE)
				err_quit("too many clients");

			/* 将新连接加入 select 监听集合，并更新最大描述符和最大数组下标。 */
			FD_SET(connfd, &allset);	/* add new descriptor to set */
			if (connfd > maxfd)
				maxfd = connfd;			/* for select */
			if (i > maxi)
				maxi = i;				/* max index in client[] array */

			/* 如果没有更多就绪描述符，重新进入 select。 */
			if (--nready <= 0)
				continue;				/* no more readable descriptors */
		}

		/* 遍历所有客户端连接，处理可读数据。 */
		for (i = 0; i <= maxi; i++) {	/* check all clients for data */
			if ( (sockfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sockfd, &rset)) {
				/* 读取客户端数据，返回 0 表示客户端关闭连接。 */
				if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
						/*connection closed by client */
					Close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				} else
					/* 正常读到数据时原样写回客户端。 */
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
 *   TCP 回显服务器，使用 select 在单进程中同时处理多个客户端连接。
 *
 * 工作流程：
 *   1. 创建、绑定并监听 TCP 套接字。
 *   2. 用 allset 保存监听套接字和所有客户端套接字。
 *   3. select 返回后，先处理新的客户端连接。
 *   4. 将新连接加入描述符集合和客户端数组。
 *   5. 遍历客户端连接，读取可读数据。
 *   6. 客户端关闭时清理描述符；正常数据则原样写回。
 */
