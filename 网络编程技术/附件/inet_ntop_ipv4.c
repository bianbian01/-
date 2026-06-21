#include	<sys/types.h>
#include	<sys/socket.h>
#include	<errno.h>
#include	<stdio.h>

#ifndef	INET_ADDRSTRLEN
#define	INET_ADDRSTRLEN		16
#endif

/* include inet_ntop */
/* 将网络字节序的二进制 IPv4 地址转换成点分十进制字符串。 */
const char *
inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	/* 把通用地址指针按字节访问，IPv4 地址正好由 4 个字节组成。 */
	const u_char *p = (const u_char *) addrptr;

	/* 这里只实现 AF_INET，也就是 IPv4 地址转换。 */
	if (family == AF_INET) {
		/* 临时缓冲区用于先生成完整的 IPv4 字符串。 */
		char	temp[INET_ADDRSTRLEN];

		/* 按 a.b.c.d 的格式把 4 个字节写成点分十进制。 */
		snprintf(temp, sizeof(temp), "%d.%d.%d.%d",
				 p[0], p[1], p[2], p[3]);

		/* 检查调用者提供的缓冲区是否足够容纳结果字符串和结束符。 */
		if (strlen(temp) >= len) {
			errno = ENOSPC;
			return (NULL);
		}

		/* 缓冲区足够时复制结果，并返回调用者传入的字符串缓冲区。 */
		strcpy(strptr, temp);
		return (strptr);
	}

	/* 不是 IPv4 时返回协议族不支持错误。 */
	errno = EAFNOSUPPORT;
	return (NULL);
}
/* end inet_ntop */

/*
 * 作用：
 *   实现一个简化版 inet_ntop，只支持把二进制 IPv4 地址转换成点分十进制字符串。
 *
 * 工作流程：
 *   1. 检查地址族是否为 AF_INET。
 *   2. 将传入的地址指针按 4 个字节读取。
 *   3. 用 snprintf 生成 a.b.c.d 形式的 IPv4 字符串。
 *   4. 检查调用者提供的缓冲区长度是否足够。
 *   5. 缓冲区足够则复制字符串并返回，空间不足或地址族不支持则返回 NULL。
 */
