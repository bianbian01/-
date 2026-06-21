//客户发送数据结束，并且服务器返回数据也结束，客户子函数才能return
#include	"unp.h"

/* TCP 客户端交互函数：支持半关闭，等待服务器回完数据后再返回。 */
void
str_cli(FILE *fp, int sockfd)
{
	/* 保存 select 参数、标准输入结束标志、描述符集合和收发缓冲区。 */
	int			maxfdp1, stdineof;
	fd_set		rset;
	char		sendline[MAXLINE], recvline[MAXLINE];

	/* stdineof 为 0 表示还可以从标准输入读取数据。 */
	stdineof = 0; //这个变量要注意，0表示客户没有发完数据，1表示客户发完数据
	FD_ZERO(&rset);

	/* 循环等待标准输入或套接字可读。 */
	for ( ; ; ) {
		/* 标准输入未结束时才继续监听它。 */
		if (stdineof == 0) //客户没有发完数据，还有输入
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

		/* 套接字可读时，读取并输出服务器返回的数据。 */
		if (FD_ISSET(sockfd, &rset)) {	/* socket is readable */
			if (Readline(sockfd, recvline, MAXLINE) == 0) {
				/* 如果标准输入已结束，此时收到 FIN 表示正常结束。 */
				if (stdineof == 1) //客户发送数据结束，此时接收到服务器TCP的FIN，表明服务器返回数据也结束
					return;		/* normal termination 正常终止 */
				else
					err_quit("str_cli: server terminated prematurely");
			}

			Fputs(recvline, stdout);
		}

		/* 标准输入可读时，读取用户输入并发送给服务器。 */
		if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */
			if (Fgets(sendline, MAXLINE, fp) == NULL) {
				/* 用户输入结束，关闭写半边但继续接收服务器剩余数据。 */
				stdineof = 1; //客户发送数据结束
				Shutdown(sockfd, SHUT_WR);	/* send FIN */
				FD_CLR(fileno(fp), &rset);
				continue;
			}

			/* 将用户输入写给服务器。 */
			Writen(sockfd, sendline, strlen(sendline));
		}
	}
}

/*
 * 作用：
 *   TCP 客户端回显交互函数，使用 select 支持标准输入结束后的 TCP 半关闭。
 *
 * 工作流程：
 *   1. 同时监听标准输入和套接字。
 *   2. 标准输入可读时，将用户输入发送给服务器。
 *   3. 标准输入结束时调用 Shutdown 关闭写方向，通知服务器不再发送数据。
 *   4. 继续读取服务器返回的数据。
 *   5. 当服务器关闭连接且本地输入已结束时，正常返回。
 */
