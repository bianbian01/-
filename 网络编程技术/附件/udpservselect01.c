/* include udpservselect01 */
#include	"unp.h"

/* 同端口 TCP/UDP 回显服务器：使用 select 同时监听 TCP 连接和 UDP 数据报。 */
int
main(int argc, char **argv)
{
	/* 保存 TCP/UDP 套接字、select 参数、缓冲区、子进程、地址和信号处理函数。 */
	int					listenfd, connfd, udpfd, nready, maxfdp1;
	char				mesg[MAXLINE];
	pid_t				childpid;
	fd_set				rset;
	ssize_t				n;
	socklen_t			len;
	const int			on = 1;
	struct sockaddr_in	cliaddr, servaddr;
	void				sig_chld(int);

		/* 4create listening TCP socket */
	/* 创建 TCP 监听套接字。 */
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	/* 初始化服务器地址，准备绑定 TCP 监听套接字。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	/* 允许端口快速复用，并绑定 TCP 监听套接字。 */
	Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	/* TCP 套接字进入监听状态。 */
	Listen(listenfd, LISTENQ);

		/* 4create UDP socket */
	/* 创建 UDP 套接字。 */
	udpfd = Socket(AF_INET, SOCK_DGRAM, 0);

	/* 初始化同一个服务器地址，准备绑定 UDP 套接字。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	/* 将 UDP 套接字绑定到同一个服务端口。 */
	Bind(udpfd, (SA *) &servaddr, sizeof(servaddr));
/* end udpservselect01 */

/* include udpservselect02 */
	/* 安装 SIGCHLD 处理函数，用于回收 TCP 子进程。 */
	Signal(SIGCHLD, sig_chld);	/* must call waitpid() */

	/* 初始化 select 集合和最大描述符加 1。 */
	FD_ZERO(&rset);
	maxfdp1 = max(listenfd, udpfd) + 1;

	/* 循环等待 TCP 或 UDP 套接字就绪。 */
	for ( ; ; ) {
		/* 每轮重新加入 TCP 监听套接字和 UDP 套接字。 */
		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);

		/* 等待任意一个套接字可读，并处理信号中断。 */
		if ( (nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0) {
			if (errno == EINTR)
				continue;		/* back to for() */
			else
				err_sys("select error");
		}

		/* TCP 监听套接字可读，说明有新的 TCP 客户端连接。 */
		if (FD_ISSET(listenfd, &rset)) {
			len = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *) &cliaddr, &len);
	
			/* 创建子进程处理 TCP 客户端。 */
			if ( (childpid = Fork()) == 0) {	/* child process */
				/* 子进程关闭监听套接字，使用 str_echo 处理连接。 */
				Close(listenfd);	/* close listening socket */
				str_echo(connfd);	/* process the request */
				exit(0);
			}

			/* 父进程关闭已连接套接字，继续监听。 */
			Close(connfd);			/* parent closes connected socket */
		}

		/* UDP 套接字可读，说明有 UDP 数据报到达。 */
		if (FD_ISSET(udpfd, &rset)) {
			len = sizeof(cliaddr);
			/* 接收 UDP 数据报并保存客户端地址。 */
			n = Recvfrom(udpfd, mesg, MAXLINE, 0, (SA *) &cliaddr, &len);

			/* 将收到的数据原样发送回 UDP 客户端。 */
			Sendto(udpfd, mesg, n, 0, (SA *) &cliaddr, len);
		}
	}
}
/* end udpservselect02 */

/*
 * 作用：
 *   同时支持 TCP 和 UDP 的回显服务器，使用 select 在同一进程中监听两类套接字。
 *
 * 工作流程：
 *   1. 创建 TCP 监听套接字，设置端口复用，绑定并监听 SERV_PORT。
 *   2. 创建 UDP 套接字，并绑定到同一个 SERV_PORT。
 *   3. 安装 SIGCHLD 处理函数，回收 TCP 子进程。
 *   4. 使用 select 同时等待 TCP 监听套接字和 UDP 套接字可读。
 *   5. 如果 TCP 有新连接，accept 后 fork 子进程调用 str_echo 处理。
 *   6. 如果 UDP 有数据报，Recvfrom 接收后 Sendto 原样返回。
 */
