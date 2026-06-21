#include	"unp.h"

/* UDP 客户端函数：发送数据报后，只接受来自目标服务器地址的回复。 */
void
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	/* 保存读写长度、发送/接收缓冲区、地址长度和回复地址。 */
	int				n;
	char			sendline[MAXLINE], recvline[MAXLINE + 1];
	socklen_t		len;
	struct sockaddr	*preply_addr;

	/* 为回复地址分配空间，用来检查数据报来源。 */
	preply_addr = Malloc(servlen);

	/* 循环从标准输入读取一行，发送给服务器并等待回复。 */
	while (Fgets(sendline, MAXLINE, fp) != NULL) {

		/* 向指定服务器地址发送 UDP 数据报。 */
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		/* 接收 UDP 回复，同时记录回复来源地址。 */
		len = servlen;
		n = Recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);

		/* 如果回复不是来自目标服务器，就忽略该数据报。 */
		if (len != servlen || memcmp(pservaddr, preply_addr, len) != 0) {
			printf("reply from %s (ignored)\n",
					Sock_ntop(preply_addr, len));
			continue;
		}

		/* 回复来源正确时，把数据转成字符串并输出。 */
		recvline[n] = 0;	/* null terminate */
		Fputs(recvline, stdout);
	}
}

/*
 * 作用：
 *   UDP 客户端回显函数，发送输入内容到服务器，并校验回复是否来自指定服务器。
 *
 * 工作流程：
 *   1. 为回复地址分配缓冲区。
 *   2. 循环读取用户输入。
 *   3. 使用 Sendto 把输入发送到目标服务器。
 *   4. 使用 Recvfrom 接收回复并取得来源地址。
 *   5. 如果来源地址不是目标服务器，则忽略该回复。
 *   6. 来源正确时输出服务器返回的数据。
 */
