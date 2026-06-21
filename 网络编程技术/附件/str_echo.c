#include	"unp.h"

/* TCP 回显服务器函数：读取客户端一行数据并原样写回。 */
void
str_echo(int sockfd)
{
	/* 保存读取长度和行缓冲区。 */
	ssize_t		n;
	char		line[MAXLINE];

	/* 循环读取客户端数据，直到客户端关闭连接。 */
	for ( ; ; ) {
		/* 读取客户端发送的一行，返回 0 表示对端关闭。 */
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

		/* 将读到的内容原样写回客户端。 */
		Writen(sockfd, line, n);
	}
}

/*
 * 作用：
 *   TCP 回显服务器核心函数，接收客户端发送的文本并原样返回。
 *
 * 工作流程：
 *   1. 循环从连接套接字读取一行数据。
 *   2. 如果读取到 0，说明客户端关闭连接，函数返回。
 *   3. 如果读取到数据，使用 Writen 原样写回客户端。
 *   4. 继续处理同一客户端的下一行数据。
 */
