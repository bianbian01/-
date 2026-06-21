#include	"unp.h"

/* UDP 客户端函数：使用 sendto/recvfrom 实现基本数据报回显客户端。 */
void
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	/* 保存读取长度和发送/接收缓冲区。 */
	int	n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	/* 循环读取用户输入，发送给服务器并等待回复。 */
	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		/* 发送一条 UDP 数据报到服务器地址。 */
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		/* 接收服务器返回的数据报，不关心回复来源地址。 */
		n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

		/* 添加字符串结束符并输出服务器回复。 */
		recvline[n] = 0;	/* null terminate */
		Fputs(recvline, stdout);
	}
}

/*
 * 作用：
 *   UDP 客户端回显函数，把标准输入内容发送给服务器，并打印服务器回复。
 *
 * 工作流程：
 *   1. 循环读取标准输入中的一行文本。
 *   2. 使用 Sendto 将文本作为 UDP 数据报发送给服务器。
 *   3. 使用 Recvfrom 等待服务器回复。
 *   4. 给接收缓冲区补字符串结束符。
 *   5. 将回复内容输出到标准输出。
 */
