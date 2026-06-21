#include	"unp.h"
#include <resolv.h>
/* 查询主机名对应的 IPv6 主机信息并打印地址列表。 */
int main(int argc, char **argv)
{
	/* 保存命令行主机名、地址列表指针、输出缓冲区和主机信息结构。 */
	char			*ptr, **pptr;
	char			str[INET6_ADDRSTRLEN];
	struct hostent	*hptr;
	//res_init();
	//_res.options |= RES_USE_INET6;

	/* 逐个处理命令行传入的主机名。 */
	while (--argc > 0) {
		ptr = *++argv;

		/* 按 IPv6 地址族查询主机信息，失败则打印错误并继续。 */
		if ( (hptr = gethostbyname2(ptr,AF_INET6)) == NULL) {
			err_msg("gethostbyname error for host: %s: %s",
					ptr, hstrerror(h_errno));
			continue;
		}

		/* 打印官方主机名。 */
		printf("official hostname: %s\n", hptr->h_name);

		/* 打印所有别名。 */
		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("\talias: %s\n", *pptr);

		/* 根据地址类型打印 IPv4 或 IPv6 地址。 */
		switch (hptr->h_addrtype) {
			case AF_INET:
			case AF_INET6:
				/* 遍历地址列表，将二进制地址转换为字符串输出。 */
				pptr = hptr->h_addr_list;
				for ( ; *pptr != NULL; pptr++)
					printf("\taddress: %s\n",
						Inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
				break;
			default:
				/* 未知地址类型时打印错误。 */
				err_ret("unknown address type");
				break;
		}
	}

	/* 所有主机名处理完毕后正常退出。 */
	exit(0);
}

/*
 * 作用：
 *   查询并显示主机名对应的 IPv6 主机信息。
 *
 * 工作流程：
 *   1. 遍历命令行传入的主机名。
 *   2. 使用 gethostbyname2 按 AF_INET6 查询主机信息。
 *   3. 打印官方主机名和别名。
 *   4. 遍历地址列表。
 *   5. 使用 Inet_ntop 将 IPv6 地址转换成字符串并输出。
 */
