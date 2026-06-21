#include	"unp.h"

/* 并发 TCP 回显服务器：使用 waitpid 方式的 SIGCHLD 处理函数。 */
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

	/* 安装必须调用 waitpid 的 SIGCHLD 处理函数，避免漏回收子进程。 */
	Signal(SIGCHLD, sig_chld);	/* must call waitpid() */

	/* 循环接受客户端连接，并处理 accept 被信号中断的情况。 */
	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
			/* 被信号中断时重新进入 accept。 */
			if (errno == EINTR)
				continue;		/* back to for() */
			else
				err_sys("accept error");
		}

		/* 创建子进程处理客户端回显。 */
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
 *   TCP 并发回显服务器，结合 waitpid 版 SIGCHLD 处理函数回收多个子进程。
 *
 * 工作流程：
 *   1. 创建、绑定并监听 TCP 套接字。
 *   2. 安装 SIGCHLD 处理函数，该处理函数应使用 waitpid 循环回收子进程。
 *   3. 循环调用 accept 接受客户端连接。
 *   4. accept 被 EINTR 中断时继续等待。
 *   5. 成功连接后 fork 子进程处理客户端。
 *   6. 父进程关闭连接套接字并继续监听。
 */
