#include	"unp.h"

/* 并发 TCP 回显服务器：安装 SIGCHLD 处理函数回收子进程。 */
int
main(int argc, char **argv)
{
	/* 保存监听套接字、连接套接字、子进程 PID、地址长度和地址结构。 */
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;
	void				sig_chld(int);

	/* 创建 IPv4 TCP 监听套接字。 */
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	/* 初始化服务器地址，绑定到本机所有网卡的 SERV_PORT 端口。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	/* 绑定并监听客户端连接。 */
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	/* 安装 SIGCHLD 信号处理函数，用于回收结束的子进程。 */
	Signal(SIGCHLD, sig_chld);

	/* 循环接受客户端连接。 */
	for ( ; ; ) {
		/* 接受一个客户端连接。 */
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		/* 创建子进程处理该客户端。 */
		if ( (childpid = Fork()) == 0) {	/* child process */
			/* 子进程关闭监听套接字，处理客户端回显。 */
			Close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process the request */
			exit(0);
		}

		/* 父进程关闭已连接套接字，继续接受连接。 */
		Close(connfd);			/* parent closes connected socket */
	}
}

/*
 * 作用：
 *   TCP 并发回显服务器，在 fork 子进程处理客户端的基础上处理 SIGCHLD 信号。
 *
 * 工作流程：
 *   1. 创建、绑定并监听 TCP 套接字。
 *   2. 安装 SIGCHLD 处理函数，回收退出的子进程。
 *   3. 循环 accept 客户端连接。
 *   4. fork 子进程处理客户端回显。
 *   5. 父进程关闭连接套接字并继续监听。
 */
