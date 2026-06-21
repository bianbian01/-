#include	"unp.h"

/* TCP 客户端交互函数：用 select 同时监听标准输入和套接字。 */
void
str_cli(FILE *fp, int sockfd)
{
	/* 保存 select 参数、描述符集合和收发缓冲区。 */
	int			maxfdp1;
	fd_set		rset;
	char		sendline[MAXLINE], recvline[MAXLINE];

	/* 初始化描述符集合。 */
	FD_ZERO(&rset);

	/* 循环等待标准输入或套接字可读。 */
	for ( ; ; ) {
		/* 每轮重新加入标准输入和套接字描述符。 */
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

		/* 套接字可读时，读取服务器回复并输出。 */
		if (FD_ISSET(sockfd, &rset)) {	/* socket is readable */
			if (Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");
			Fputs(recvline, stdout);
		}

		/* 标准输入可读时，读取用户输入并发送给服务器。 */
		if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */
			if (Fgets(sendline, MAXLINE, fp) == NULL)
				return;		/* all done */
			Writen(sockfd, sendline, strlen(sendline));
		}
	}
}

/*
 * 作用：
 *   TCP 客户端回显交互函数，使用 select 同时处理用户输入和服务器回复。
 *
 * 工作流程：
 *   1. 初始化描述符集合。
 *   2. 每轮把标准输入和套接字加入 select 监听集合。
 *   3. 如果套接字可读，读取服务器数据并输出。
 *   4. 如果标准输入可读，读取用户输入并写给服务器。
 *   5. 标准输入结束时返回。
 */
