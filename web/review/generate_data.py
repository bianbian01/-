from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
WEB_DIR = Path(__file__).resolve().parent
OUT = WEB_DIR / "data.js"

SKIP_DIRS = {".git", ".vscode", "web"}
DOC_EXT = {".md", ".pdf", ".ppt", ".pptx", ".txt"}
CODE_EXT = {".c", ".h", ".py", ".sh", ".s", ".cgi", ".conf", ".yml", ".yaml"}

KEY_FILES = [
    {
        "path": "网络编程技术/附件/tcpserv01.c",
        "lang": "c",
        "explanation": "TCP 并发服务端基础骨架，体现 socket/bind/listen/accept 主流程。",
        "capability": "支持建立 TCP 监听并处理客户端连接",
        "limitation": "示例级代码，未覆盖生产环境异常与高并发治理",
    },
    {
        "path": "网络编程技术/附件/str_cli.c",
        "lang": "c",
        "explanation": "TCP 客户端读写循环，展示客户端与服务端回射交互。",
        "capability": "支持标准输入到套接字的数据发送",
        "limitation": "未引入协议封包、重试策略和完整错误恢复",
    },
    {
        "path": "计算机系统安全/实验/3. Buffer_overflow/Buffer_Overflow_Server_实验/server-code/stack.c",
        "lang": "c",
        "explanation": "缓冲区溢出实验样例，展示脆弱拷贝路径和栈布局。",
        "capability": "可用于演示栈溢出攻击机理",
        "limitation": "故意保留漏洞，不可直接用于安全生产代码",
    },
    {
        "path": "计算机系统安全/实验/5. Format-String _Vulnerability_实验/server-code/format.c",
        "lang": "c",
        "explanation": "格式化字符串漏洞样例，说明未受控 printf 的风险。",
        "capability": "可复现实验中格式化字符串读写影响",
        "limitation": "为教学用途，缺少输入校验与加固",
    },
    {
        "path": "计算机系统安全/实验/8. Spectre 攻击实验/Labsetup/SpectreAttack.c",
        "lang": "c",
        "explanation": "Spectre 侧信道攻击实验代码，展示推测执行+缓存时序泄露。",
        "capability": "可演示基于 Flush+Reload 的信息侧信道",
        "limitation": "依赖特定硬件和实验环境，结果受平台影响",
    },
    {
        "path": "网络编程技术/网络编程技术_最终版.md",
        "lang": "md",
        "explanation": "网络编程课程复习主文档，按考点组织函数与代码骨架。",
        "capability": "提供系统化复习路径和函数速查",
        "limitation": "偏考试导向，不是完整工程文档",
    },
]


def collect_files() -> list[Path]:
    files: list[Path] = []
    for p in ROOT.rglob("*"):
        rel = p.relative_to(ROOT)
        if any(part in SKIP_DIRS for part in rel.parts):
            continue
        if p.is_file() and not p.name.startswith("."):
            files.append(p)
    return files


def build_tree() -> list[str]:
    lines = ["review/"]
    top_dirs = sorted([p for p in ROOT.iterdir() if p.is_dir() and p.name not in {".git", ".vscode", "web"}], key=lambda x: x.name)
    for i, d in enumerate(top_dirs):
        last_top = i == len(top_dirs) - 1
        pfx = "└── " if last_top else "├── "
        lines.append(f"{pfx}{d.name}/")

        second = sorted([x for x in d.iterdir() if x.is_dir()], key=lambda x: x.name)
        files = sorted([x for x in d.iterdir() if x.is_file()], key=lambda x: x.name)

        level2 = second[:8]
        for j, s in enumerate(level2):
            is_last = j == len(level2) - 1 and not files
            child_pfx = "    " if last_top else "│   "
            branch = "└── " if is_last else "├── "
            lines.append(f"{child_pfx}{branch}{s.name}/")

            third = sorted([x for x in s.iterdir()], key=lambda x: x.name)[:5]
            for k, t in enumerate(third):
                child2 = child_pfx + ("    " if is_last else "│   ")
                branch2 = "└── " if k == len(third) - 1 else "├── "
                suffix = "/" if t.is_dir() else ""
                lines.append(f"{child2}{branch2}{t.name}{suffix}")

        shown = len(level2)
        if len(second) > shown:
            child_pfx = "    " if last_top else "│   "
            lines.append(f"{child_pfx}└── ... ({len(second)-shown} more directories)")

        if files:
            child_pfx = "    " if last_top else "│   "
            for j, f in enumerate(files[:6]):
                branch = "└── " if j == min(len(files), 6) - 1 else "├── "
                lines.append(f"{child_pfx}{branch}{f.name}")
            if len(files) > 6:
                lines.append(f"{child_pfx}└── ... ({len(files)-6} more files)")

    return lines


def read_excerpt(path: Path, max_lines: int = 140) -> str:
    try:
        text = path.read_text(encoding="utf-8", errors="ignore")
    except Exception:
        return ""
    lines = text.splitlines()
    return "\n".join(lines[:max_lines])


def main() -> None:
    files = collect_files()

    ext_count: dict[str, int] = {}
    top_count: dict[str, int] = {}
    docs = 0
    code = 0

    for p in files:
        rel = p.relative_to(ROOT)
        ext = p.suffix.lower() or "<none>"
        ext_count[ext] = ext_count.get(ext, 0) + 1

        top = rel.parts[0]
        top_count[top] = top_count.get(top, 0) + 1

        if ext in DOC_EXT:
            docs += 1
        if ext in CODE_EXT:
            code += 1

    top_dirs = sorted(top_count.items(), key=lambda x: x[1], reverse=True)
    ext_stats = sorted(ext_count.items(), key=lambda x: x[1], reverse=True)

    key_files = []
    for item in KEY_FILES:
        target = ROOT / item["path"]
        if not target.exists():
            continue
        content = read_excerpt(target)
        lines = len(content.splitlines()) if content else 0
        key_files.append(
            {
                **item,
                "lines": lines,
                "content": content,
            }
        )

    data = {
        "projectName": "review",
        "summary": "面向课程考试的综合复习仓库，融合知识点文档、历年重点梳理与安全/网络实验示例代码。",
        "focus": ["复习资料结构化", "安全实验代码审阅", "网络编程样例归类"],
        "intro": "仓库覆盖区块链、操作系统、汇编、网络编程、网络通信协议、软件体系结构、计算机系统安全等课程内容。以 Markdown/PDF 复习资料为主体，并包含可运行的 C/Python/Shell 实验代码用于理解网络与安全原理。",
        "positioning": [
            "多课程复习资料中台：统一管理各课程考点与速记内容",
            "安全教学实验库：保留漏洞样例用于实验复现与原理理解",
            "网络编程案例集：围绕 TCP/UDP、select/poll、地址转换等核心主题",
        ],
        "features": [
            "课程复习文档按主题与版本组织，便于快速定位重点",
            "安全实验代码覆盖缓冲区溢出、格式化字符串、竞争条件、Spectre、Meltdown 等专题",
            "网络编程代码包含 TCP/UDP 客户端/服务端与 I/O 复用示例",
            "同一知识点存在多个修订版文档，适合考前迭代整理",
        ],
        "coreModules": [
            {"name": "计算机系统安全", "desc": "SEED 安全实验相关资料与代码，偏攻防实验与漏洞机理学习"},
            {"name": "网络编程技术", "desc": "网络套接字编程复习与 C 语言示例代码集合"},
            {"name": "网络通信协议", "desc": "协议分析、抓包解题与考试模板化复习资料"},
            {"name": "操作系统 / 汇编 / 区块链 / 软件体系结构", "desc": "课程知识点梳理与考前记忆清单"},
            {"name": "web/review", "desc": "本次新增的网站审阅层，独立于原始资料和实验代码"},
        ],
        "techStack": ["Markdown", "PDF/PPTX", "C", "Python", "Shell", "HTML/CSS/JavaScript"],
        "stats": {
            "totalFiles": len(files),
            "totalCodeFiles": code,
            "totalDocs": docs,
            "topLevelModules": len(top_count),
        },
        "topDirs": [{"name": k, "count": v} for k, v in top_dirs],
        "extensionStats": [{"ext": k, "count": v} for k, v in ext_stats[:12]],
        "tree": build_tree(),
        "keyFiles": key_files,
        "run": [
            "进入仓库根目录：cd /home/runner/work/review/review",
            "启动本地静态服务：python -m http.server 8000",
            "浏览器访问：http://127.0.0.1:8000/web/review/index.html",
        ],
        "progress": {
            "done": [
                "已完成仓库全量文件扫描与类型统计",
                "已按课程/实验职责提炼核心模块说明",
                "已实现目录树、模块信息、关键代码在线审阅界面",
                "已实现基础语法高亮和核心文件能力/限制标注",
            ],
            "todo": [
                "补充按关键字全文检索所有资料内容",
                "为大文件提供分段加载与分页浏览",
            ],
        },
        "roadmap": [
            "增加 PDF/PPT 文档预览与章节跳转索引",
            "增加关键实验代码的调用关系图与流程图",
            "增加按课程、文件类型、更新时间的交互筛选",
            "引入自动化脚本定期刷新数据并生成变更报告",
        ],
        "capabilities": [
            "可视化呈现项目概况、技术栈、目录与模块职责",
            "可在线查看关键代码节选并辅助快速理解",
            "可显示当前仓库的完成情况和可改进方向",
        ],
        "limitations": [
            "代码查看为关键文件节选，不是完整 IDE 级浏览",
            "语法高亮为轻量实现，语言覆盖有限",
            "目录树做了层级与数量裁剪以控制页面长度",
            "仓库中的实验漏洞代码为教学用途，不应直接用于生产系统",
        ],
    }

    OUT.write_text("window.REPO_DATA = " + json.dumps(data, ensure_ascii=False, indent=2) + ";\n", encoding="utf-8")
    print(f"generated: {OUT}")


if __name__ == "__main__":
    main()
