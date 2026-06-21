#include	"unp.h"

/* 查询主机名对应的官方名称、别名和 IP 地址。 */
int
main(int argc, char **argv)
{
	/* 保存命令行主机名、地址列表指针、输出缓冲区和主机信息结构。 */
	char			*ptr, **pptr;
	char			str[INET6_ADDRSTRLEN]; //在unp.h中定义INET6_ADDRSTRLEN是46
	struct hostent	*hptr;

	/* 逐个处理命令行传入的主机名。 */
	while (--argc > 0) {
		ptr = *++argv; //先运算++，然后是*

		/* 根据主机名查询主机信息，失败则打印错误并继续下一个主机名。 */
		if ( (hptr = gethostbyname(ptr)) == NULL) {
			err_msg("gethostbyname error for host: %s: %s",
					ptr, hstrerror(h_errno)); //const char *hstrerror(int err)用来依参数err的错误代码来查询socket错误原因的描述字符串， 然后将该字符串指针返回
			continue;
		}

		/* 打印官方主机名。 */
		printf("official hostname: %s\n", hptr->h_name);

		/* 打印该主机的所有别名。 */
		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("\talias: %s\n", *pptr);

		/* 根据地址类型打印所有地址。 */
		switch (hptr->h_addrtype) {
		case AF_INET:
#ifdef	AF_INET6
		case AF_INET6:
#endif
			/* 将二进制地址转换成字符串后输出。 */
			pptr = hptr->h_addr_list;
			for ( ; *pptr != NULL; pptr++)
				printf("\taddress: %s\n",
					Inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
			break;

		default:
			/* 遇到未知地址类型时打印错误。 */
			err_ret("unknown address type");
			break;
		}
	}

	/* 所有主机名处理完毕后正常退出。 */
	exit(0);
}

/*
 * 作用：
 *   查询并显示主机名的官方名称、别名和 IP 地址列表。
 *
 * 工作流程：
 *   1. 遍历命令行传入的每个主机名。
 *   2. 使用 gethostbyname 查询主机信息。
 *   3. 打印官方主机名和所有别名。
 *   4. 根据地址类型遍历地址列表。
 *   5. 使用 Inet_ntop 将地址转换为字符串并输出。
 */
