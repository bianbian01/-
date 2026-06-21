#include	"unp.h"

/* SIGCHLD 信号处理函数：用 wait 回收一个结束的子进程。 */
void
sig_chld(int signo)
{
	/* 保存结束的子进程 PID 和退出状态。 */
	pid_t	pid;
	int		stat;

	/* 等待并回收一个已经终止的子进程。 */
	pid = wait(&stat);
	printf("child %d terminated\n", pid);
	return;
}

/*
 * 作用：
 *   作为 SIGCHLD 信号处理函数，回收已经退出的子进程，避免产生僵死进程。
 *
 * 工作流程：
 *   1. 父进程收到 SIGCHLD 信号后进入该函数。
 *   2. 调用 wait 回收一个终止的子进程。
 *   3. 打印被回收子进程的 PID。
 *   4. 返回原来的执行流程。
 */
