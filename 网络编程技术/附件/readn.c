/* include readn */
#include	"unp.h"

/* 从描述符 fd 中尽量读取 n 个字节，处理短读和信号中断。 */
ssize_t						/* Read "n" bytes from a descriptor. */
readn(int fd, void *vptr, size_t n)
{
	/* nleft 表示还需要读取的字节数，ptr 指向当前写入缓冲区的位置。 */
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	/* 初始化缓冲区指针和剩余读取长度。 */
	ptr = vptr;
	nleft = n;

	/* 循环读取，直到读满 n 字节、遇到 EOF 或发生真正错误。 */
	while (nleft > 0) {
		if ( (nread = read(fd, ptr, nleft)) < 0) {
			/* 如果被信号中断，则本轮当作没读到数据，继续重试。 */
			if (errno == EINTR)
				nread = 0;		/* and call read() again */
			else
				/* 其他错误直接返回 -1。 */
				return(-1);
		} else if (nread == 0)
			/* read 返回 0 表示对端关闭或到达文件结束。 */
			break;				/* EOF */

		/* 根据本次实际读取字节数，更新剩余长度和缓冲区位置。 */
		nleft -= nread;
		ptr   += nread;
	}

	/* 返回实际读取到的字节数，可能小于 n。 */
	return(n - nleft);		/* return >= 0 */
}
/* end readn */

/* readn 的包裹函数：读取失败时直接输出错误并终止程序。 */
ssize_t
Readn(int fd, void *ptr, size_t nbytes)
{
	ssize_t		n;

	/* 调用基础版本 readn，并统一处理错误。 */
	if ( (n = readn(fd, ptr, nbytes)) < 0)
		err_sys("readn error");
	return(n);
}

/*
 * 作用：
 *   提供可靠读取函数，尽量从描述符中读满指定的 n 个字节。
 *
 * 工作流程：
 *   1. 记录剩余需要读取的字节数和当前缓冲区位置。
 *   2. 循环调用 read，每次从当前位置继续读取剩余数据。
 *   3. 如果 read 被信号中断，则继续重试。
 *   4. 如果遇到 EOF 或发生错误，则提前结束。
 *   5. 返回实际读取到的字节数；Readn 包裹函数会统一处理读取错误。
 */
