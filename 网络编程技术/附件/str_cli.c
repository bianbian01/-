#include	"unp.h"

/* TCP 客户端交互函数：读取标准输入，发送给服务器，再打印回复。 */
void
str_cli(FILE *fp, int sockfd)
{
	/* 保存发送和接收缓冲区。 */
	char	sendline[MAXLINE], recvline[MAXLINE];

	/* 循环读取用户输入，每行发送一次。 */
	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		/* 将用户输入发送到 TCP 连接。 */
		Writen(sockfd, sendline, strlen(sendline));

		/* 读取服务器回显的一行数据，若提前关闭则报错。 */
		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		/* 输出服务器返回的内容。 */
		Fputs(recvline, stdout);
	}
}

/*
 * 作用：
 *   TCP 客户端回显函数，把标准输入逐行发送给服务器，并打印服务器回显。
 *
 * 工作流程：
 *   1. 从标准输入读取一行文本。
 *   2. 使用 Writen 将文本写入 TCP 连接。
 *   3. 使用 Readline 读取服务器返回的一行数据。
 *   4. 将服务器回复输出到标准输出。
 *   5. 标准输入结束时函数返回。
 */
