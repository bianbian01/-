#include	"unp.h"

/* TCP daytime 客户端增强版：通过主机名和服务名连接服务器并读取时间。 */
int
main(int argc, char **argv)
{
	/* 保存套接字、读取长度、接收缓冲区、服务器地址、主机信息和服务信息。 */
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;
	struct in_addr		**pptr;
	struct hostent		*hp;
	struct servent		*sp;

	/* 检查命令行参数，需要主机名和服务名两个参数。 */
	if (argc != 3)
		err_quit("usage: daytimetcpcli1 <hostname> <service>");

	/* 根据主机名查询主机地址列表。 */
	if ( (hp = gethostbyname(argv[1])) == NULL)
		err_quit("hostname error for %s: %s", argv[1], hstrerror(h_errno));

	/* 根据服务名查询 TCP 服务端口。 */
	if ( (sp = getservbyname(argv[2], "tcp")) == NULL)
		err_quit("getservbyname error for %s", argv[2]);

	/* 依次尝试主机名对应的每一个 IPv4 地址，直到连接成功。 */
	pptr = (struct in_addr **) hp->h_addr_list;
	for ( ; *pptr != NULL; pptr++) {
		/* 为当前地址创建 TCP 套接字。 */
		sockfd = Socket(AF_INET, SOCK_STREAM, 0);

		/* 设置服务器地址、服务端口和当前尝试的 IP 地址。 */
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = sp->s_port;
		memcpy(&servaddr.sin_addr, *pptr, sizeof(struct in_addr));
		printf("trying %s\n",
			   Sock_ntop((SA *) &servaddr, sizeof(servaddr)));

		/* 当前地址连接成功则退出循环，否则关闭套接字继续尝试下一个地址。 */
		if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) == 0)
			break;		/* success */
		err_ret("connect error");
		close(sockfd);
	}

	/* 所有地址都连接失败时终止程序。 */
	if (*pptr == NULL)
		err_quit("unable to connect");

	/* 连接成功后读取服务器返回的 daytime 字符串并打印。 */
	while ( (n = Read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		Fputs(recvline, stdout);
	}

	/* 正常结束客户端程序。 */
	exit(0);
}

/*
 * 作用：
 *   通过主机名和服务名连接 TCP daytime 服务器，并输出服务器返回的时间。
 *
 * 工作流程：
 *   1. 从命令行读取主机名和服务名。
 *   2. 使用 gethostbyname 查询主机对应的地址列表。
 *   3. 使用 getservbyname 查询服务对应的 TCP 端口。
 *   4. 逐个尝试主机地址，直到建立 TCP 连接。
 *   5. 从服务器读取时间字符串并输出。
 *   6. 如果所有地址都连接失败，则报错退出。
 */
