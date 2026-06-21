#include	"unp.h"

/* 检测当前主机的字节序：大端、小端或未知格式。 */
int
main(int argc, char **argv)
{
	/* 用 union 让同一段内存既能按 short 访问，也能按字节数组访问。 */
	union {
	  short  s;
      char   c[sizeof(short)];
    } un;

	/* 写入一个已知的 16 位数值，通过观察低地址处的字节判断字节序。 */
	un.s = 0x0102;
	printf("%s: ", CPU_VENDOR_OS);

	/* short 正常为 2 字节时，比较两个字节在内存中的排列顺序。 */
	if (sizeof(short) == 2) {
		/* 高位字节 0x01 在前，说明是大端字节序。 */
		if (un.c[0] == 1 && un.c[1] == 2)
			printf("big-endian\n");
		/* 低位字节 0x02 在前，说明是小端字节序。 */
		else if (un.c[0] == 2 && un.c[1] == 1)
			printf("little-endian\n");
		/* 两种常见排列都不符合，输出未知。 */
		else
			printf("unknown\n");
	} else
		/* 如果 short 不是 2 字节，直接输出实际大小。 */
		printf("sizeof(short) = %d\n", sizeof(short));

	/* 程序正常结束。 */
	exit(0);
}

/*
 * 作用：
 *   判断当前主机采用大端字节序还是小端字节序。
 *
 * 工作流程：
 *   1. 在 union 中写入固定的 short 值 0x0102。
 *   2. 按字节查看这两个字节在内存中的排列顺序。
 *   3. 如果内存低地址先存 0x01，则说明是大端；如果先存 0x02，则说明是小端。
 *   4. 打印判断结果后退出程序。
 */
