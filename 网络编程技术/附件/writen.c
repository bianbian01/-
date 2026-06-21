/* include writen */
#include	"unp.h"

/* 向描述符 fd 写入 n 个字节，处理短写和信号中断。 */
ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n)
{
	/* nleft 表示还需要写入的字节数，ptr 指向当前待写数据的位置。 */
	size_t		nleft;
	ssize_t		nwritten;
	const char	*ptr;

	/* 初始化待写缓冲区指针和剩余写入长度。 */
	ptr = vptr;
	nleft = n;

	/* 循环写入，直到 n 个字节全部写完或发生真正错误。 */
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
			/* 如果写操作被信号中断，则本轮当作没写入数据，继续重试。 */
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				/* 其他错误直接返回 -1。 */
				return(-1);			/* error */
		}

		/* 根据本次实际写入字节数，更新剩余长度和缓冲区位置。 */
		nleft -= nwritten;
		ptr   += nwritten;
	}

	/* 全部写入成功时返回请求写入的字节数。 */
	return(n);
}
/* end writen */

/* writen 的包裹函数：写入失败或未写满时直接输出错误并终止程序。 */
void
Writen(int fd, void *ptr, size_t nbytes)
{
	/* 调用基础版本 writen，并统一检查是否完整写入。 */
	if (writen(fd, ptr, nbytes) != nbytes)
		err_sys("writen error");
}

/*
 * 作用：
 *   提供可靠写入函数，尽量向描述符中写满指定的 n 个字节。
 *
 * 工作流程：
 *   1. 记录剩余需要写入的字节数和当前待写数据位置。
 *   2. 循环调用 write，每次从当前位置继续写入剩余数据。
 *   3. 如果 write 被信号中断，则继续重试。
 *   4. 如果发生真正错误，则返回 -1。
 *   5. 全部写入成功后返回 n；Writen 包裹函数会统一处理写入失败。
 */
