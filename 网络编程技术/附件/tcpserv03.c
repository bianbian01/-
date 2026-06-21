#include	"unp.h"

/* 并发 TCP 回显服务器：处理 accept 被 SIGCHLD 中断的情况。 */
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

	/* 初始化服务器地址，绑定到 SERV_PORT。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	/* 绑定并监听客户端连接。 */
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	/* 安装 SIGCHLD 处理函数。 */
	Signal(SIGCHLD, sig_chld);

	/* 循环接受客户端连接，并显式处理 accept 错误。 */
	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
			/* accept 被信号中断时继续等待连接。 */
			if (errno == EINTR)
				continue;		/* back to for() */
			else
				/* 其他 accept 错误直接终止。 */
				err_sys("accept error");
		}

		/* 创建子进程处理该客户端。 */
		if ( (childpid = Fork()) == 0) {	/* child process */
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
 *   TCP 并发回显服务器，演示 accept 被信号中断时如何继续运行。
 *
 * 工作流程：
 *   1. 创建、绑定并监听 TCP 套接字。
 *   2. 安装 SIGCHLD 处理函数。
 *   3. 使用原始 accept 接受连接。
 *   4. 如果 accept 因 EINTR 中断，则继续循环。
 *   5. 成功连接后 fork 子进程调用 str_echo 处理客户端。
 *   6. 父进程关闭连接套接字并继续等待。
 */
