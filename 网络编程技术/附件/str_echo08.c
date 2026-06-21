#include	"unp.h"

/* TCP 服务器处理函数：读取两个整数，返回它们的和。 */
void
str_echo(int sockfd)
{
	/* 保存两个操作数、读取长度和行缓冲区。 */
	long		arg1, arg2;
	ssize_t		n;
	char		line[MAXLINE];

	/* 循环读取客户端请求，直到客户端关闭连接。 */
	for ( ; ; ) {
		/* 读取客户端发送的一行数据。 */
		if ( (n = Readline(sockfd, line, MAXLINE)) == 0)
			return;		/* connection closed by other end */

		/* 如果成功解析两个整数，就计算并格式化它们的和。 */
		if (sscanf(line, "%ld%ld", &arg1, &arg2) == 2)
			snprintf(line, sizeof(line), "%ld\n", arg1 + arg2);
		else
			/* 输入格式不正确时返回错误提示。 */
			snprintf(line, sizeof(line), "input error\n");

		/* 将计算结果或错误提示写回客户端。 */
		n = strlen(line);
		Writen(sockfd, line, n);
	}
}

/*
 * 作用：
 *   TCP 服务器处理函数，接收客户端发来的两个整数并返回求和结果。
 *
 * 工作流程：
 *   1. 循环从连接套接字读取一行文本。
 *   2. 尝试从文本中解析两个 long 整数。
 *   3. 解析成功则计算两数之和并格式化结果。
 *   4. 解析失败则生成 input error 提示。
 *   5. 将结果写回客户端，继续等待下一次请求。
 */
