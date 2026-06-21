#include	"unp.h"

/* SIGCHLD 信号处理函数：用 waitpid 非阻塞地回收所有已结束子进程。 */
void
sig_chld(int signo)
{
	/* 保存结束的子进程 PID 和退出状态。 */
	pid_t	pid;
	int		stat;

	/* 循环回收所有已经终止的子进程，WNOHANG 避免阻塞。 */
	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}

/*
 * 作用：
 *   作为 SIGCHLD 信号处理函数，使用 waitpid 回收所有已退出的子进程。
 *
 * 工作流程：
 *   1. 父进程收到 SIGCHLD 信号后进入该函数。
 *   2. 调用 waitpid(-1, ..., WNOHANG) 非阻塞检查任意子进程。
 *   3. 只要还有已终止子进程，就继续回收并打印 PID。
 *   4. 没有可回收子进程时返回。
 */
