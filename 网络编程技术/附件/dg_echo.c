#include	"unp.h"

/* UDP 回显服务器函数：收到客户端数据报后原样发回。 */
void
dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	/* 保存接收长度、客户端地址长度和消息缓冲区。 */
	int			n;
	socklen_t	len;
	char		mesg[MAXLINE];

	/* 服务器循环运行，持续接收并回显 UDP 数据报。 */
	for ( ; ; ) {
		/* 每次接收前重置客户端地址长度。 */
		len = clilen;

		/* 接收客户端数据报，并记录客户端地址。 */
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

		/* 将收到的数据原样发送回该客户端。 */
		Sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}

/*
 * 作用：
 *   UDP 回显服务器核心函数，接收客户端数据报并原样返回。
 *
 * 工作流程：
 *   1. 进入无限循环等待 UDP 数据报。
 *   2. 使用 Recvfrom 接收消息并保存客户端地址。
 *   3. 使用 Sendto 将同样的消息发送回该客户端。
 *   4. 继续等待下一条数据报。
 */
