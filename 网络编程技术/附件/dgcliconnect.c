#include	"unp.h"

/* UDP 客户端函数：先 connect UDP 套接字，再用 read/write 收发数据。 */
void
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	/* 保存读取长度和发送/接收缓冲区。 */
	int		n;
	char	sendline[MAXLINE], recvline[MAXLINE + 1];

	/* 连接 UDP 套接字，使其固定默认对端地址。 */
	Connect(sockfd, (SA *) pservaddr, servlen);

	/* 循环读取用户输入，发送给服务器并读取回复。 */
	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		/* 已 connect 的 UDP 套接字可以直接使用 Write 发送。 */
		Write(sockfd, sendline, strlen(sendline));

		/* 从已 connect 的 UDP 套接字读取服务器回复。 */
		n = Read(sockfd, recvline, MAXLINE);

		/* 添加字符串结束符并输出回复内容。 */
		recvline[n] = 0;	/* null terminate */
		Fputs(recvline, stdout);
	}
}

/*
 * 作用：
 *   演示 UDP 套接字 connect 后的客户端回显流程。
 *
 * 工作流程：
 *   1. 对 UDP 套接字调用 connect，设置默认服务器地址。
 *   2. 循环从标准输入读取一行数据。
 *   3. 使用 Write 发送数据到默认服务器。
 *   4. 使用 Read 接收服务器回复。
 *   5. 将回复内容输出到标准输出。
 */
