#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<errno.h>
#include	<string.h>

/* Delete following line if your system's headers already DefinE this
   function prototype */
int		 inet_aton(const char *, struct in_addr *);

/* include inet_pton */
/* 将点分十进制 IPv4 字符串转换成网络字节序的二进制地址。 */
int
inet_pton(int family, const char *strptr, void *addrptr)
{
	/* 这里只实现 AF_INET，也就是 IPv4 地址转换。 */
    if (family == AF_INET) {
		/* 临时保存 inet_aton 转换出来的 IPv4 地址。 */
    	struct in_addr  in_val;

		/* inet_aton 转换成功时，把结果复制到调用者提供的地址空间。 */
        if (inet_aton(strptr, &in_val)) {
            memcpy(addrptr, &in_val, sizeof(struct in_addr));
            return (1);
        }

		/* 字符串不是合法 IPv4 地址时返回 0。 */
		return(0);
    }

	/* 不是 IPv4 时返回协议族不支持错误。 */
	errno = EAFNOSUPPORT;
    return (-1);
}
/* end inet_pton */

/*
 * 作用：
 *   实现一个简化版 inet_pton，只支持把点分十进制 IPv4 字符串转换成二进制地址。
 *
 * 工作流程：
 *   1. 检查地址族是否为 AF_INET。
 *   2. 使用 inet_aton 尝试解析传入的 IPv4 字符串。
 *   3. 如果解析成功，将结果复制到调用者提供的地址缓冲区，并返回 1。
 *   4. 如果字符串格式不合法，返回 0。
 *   5. 如果地址族不是 IPv4，设置 errno 并返回 -1。
 */
