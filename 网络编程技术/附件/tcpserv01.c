#include	"unp.h"

/* 并发 TCP 回显服务器：每个客户端由一个子进程处理。 */
int
main(int argc, char **argv)
{
	/* 保存监听套接字、连接套接字、子进程 PID、地址长度和地址结构。 */
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	/* 创建 IPv4 TCP 监听套接字。 */
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	/* 初始化服务器地址，绑定到本机所有网卡的 SERV_PORT 端口。 */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	/* 绑定监听套接字到服务器地址。 */
	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	/* 开始监听客户端连接。 */
	Listen(listenfd, LISTENQ);

	/* 循环接受客户端连接。 */
	for ( ; ; ) {
		/* 接受一个客户端连接，并保存客户端地址。 */
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		/* 创建子进程处理该客户端。 */
		if ( (childpid = Fork()) == 0) {	/* child process */
			/* 子进程关闭监听套接字，只处理已连接套接字。 */
			Close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process the request */
			exit(0);
		}

		/* 父进程关闭已连接套接字，继续监听新客户端。 */
		Close(connfd);			/* parent closes connected socket */
	}
}

/*
 * 作用：
 *   TCP 并发回显服务器，为每个客户端 fork 一个子进程处理回显。
 *
 * 工作流程：
 *   1. 创建 TCP 监听套接字并绑定到 SERV_PORT。
 *   2. 调用 listen 进入监听状态。
 *   3. 循环 accept 客户端连接。
 *   4. 每接受一个连接就 fork 子进程。
 *   5. 子进程关闭监听套接字并调用 str_echo 处理客户端。
 *   6. 父进程关闭已连接套接字并继续接受新连接。
 */
