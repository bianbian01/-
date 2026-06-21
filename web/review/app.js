(function () {
  const data = window.REPO_DATA;
  if (!data) return;

  const byId = (id) => document.getElementById(id);
  const li = (arr) => `<ul class="clean">${arr.map((x) => `<li>${x}</li>`).join('')}</ul>`;

  function renderHero() {
    byId('top').innerHTML = `
      <h1>${data.projectName} · 仓库可视化审阅</h1>
      <p>${data.summary}</p>
      <p>聚焦：${data.focus.join(' / ')}</p>
      <div class="badges">${data.techStack.map((t) => `<span class="badge">${t}</span>`).join('')}</div>
    `;
  }

  function renderOverview() {
    const s = data.stats;
    byId('overview').innerHTML = `
      <h2>项目简介</h2>
      <p>${data.intro}</p>
      <div class="grid">
        <div class="metric"><b>${s.totalFiles}</b><span>总文件数</span></div>
        <div class="metric"><b>${s.totalCodeFiles}</b><span>代码文件</span></div>
        <div class="metric"><b>${s.totalDocs}</b><span>文档文件</span></div>
        <div class="metric"><b>${s.topLevelModules}</b><span>一级模块目录</span></div>
      </div>
      <h3>项目定位</h3>
      ${li(data.positioning)}
    `;
  }

  function renderFeatures() {
    byId('features').innerHTML = `
      <h2>功能特性</h2>
      ${li(data.features)}
      <h3>核心模块（按内容职责分组）</h3>
      ${li(data.coreModules.map((m) => `<b>${m.name}</b>：${m.desc}`))}
    `;
  }

  function renderArchitecture() {
    const topDirs = data.topDirs.map((d) => `<span>${d.name} (${d.count})</span>`).join('');
    const ext = data.extensionStats.map((d) => `<span>${d.ext}: ${d.count}</span>`).join('');
    byId('architecture').innerHTML = `
      <h2>技术架构</h2>
      <h3>技术栈</h3>
      <div class="tags">${data.techStack.map((t) => `<span>${t}</span>`).join('')}</div>
      <h3>目录规模分布</h3>
      <div class="tags">${topDirs}</div>
      <h3>文件类型分布</h3>
      <div class="tags">${ext}</div>
      <p class="note">说明：该仓库以复习文档（Markdown/PDF）+ 安全/网络实验样例代码（C/Python/Shell）构成，网站层与原业务资料完全隔离在 <code>web/review</code> 目录。</p>
    `;
  }

  function renderTree() {
    byId('tree').innerHTML = `
      <h2>文件目录树</h2>
      <div class="tree"><div class="tree-node" id="tree-node"></div></div>
      <p class="note">展示到 3 级目录，省略二进制大文件详情以保证可读性。</p>
    `;
    byId('tree-node').textContent = data.tree.join('\n');
  }

  function highlight(code, lang) {
    let out = code
      .replace(/&/g, '&amp;')
      .replace(/</g, '&lt;')
      .replace(/>/g, '&gt;');

    out = out.replace(/(\/\/[^
]*|#[^
]*|\/\*[\s\S]*?\*\/)/g, '<span class="com">$1</span>');
    out = out.replace(/("(?:[^"\\]|\\.)*"|'(?:[^'\\]|\\.)*')/g, '<span class="str">$1</span>');
    out = out.replace(/\b(\d+)\b/g, '<span class="num">$1</span>');

    const keywords = {
      c: ['int','char','void','return','if','else','for','while','define','include','unsigned','long','short','struct','typedef','static','volatile','sizeof','main','printf','fread','strcpy'],
      py: ['def','return','import','from','for','while','if','elif','else','class','try','except','with','as','in','print','lambda'],
      md: ['#','##','###']
    };

    const ks = keywords[lang] || [];
    if (ks.length) {
      const r = new RegExp(`\\b(${ks.join('|')})\\b`, 'g');
      out = out.replace(r, '<span class="kw">$1</span>');
    }
    return out;
  }

  function renderCode() {
    byId('code').innerHTML = `
      <h2>核心代码说明（在线查看）</h2>
      <div class="code-layout">
        <div class="file-list" id="file-list"></div>
        <div class="code-panel">
          <div class="code-head">
            <strong id="code-title"></strong>
            <span id="code-lang"></span>
          </div>
          <div class="note" style="padding:10px;border-bottom:1px solid var(--border)" id="code-desc"></div>
          <pre><code id="code-content"></code></pre>
        </div>
      </div>
    `;

    const fileList = byId('file-list');
    const files = data.keyFiles;

    function activate(index) {
      [...fileList.querySelectorAll('.file-item')].forEach((el, i) => {
        el.classList.toggle('active', i === index);
      });
      const f = files[index];
      byId('code-title').textContent = f.path;
      byId('code-lang').textContent = `${f.lang.toUpperCase()} · ${f.lines} 行（节选）`;
      byId('code-desc').textContent = `${f.explanation} | 已有能力：${f.capability} | 当前限制：${f.limitation}`;
      byId('code-content').innerHTML = highlight(f.content, f.lang);
    }

    files.forEach((f, i) => {
      const div = document.createElement('div');
      div.className = 'file-item';
      div.innerHTML = `<b>${f.path}</b><small>${f.explanation}</small>`;
      div.onclick = () => activate(i);
      fileList.appendChild(div);
    });

    if (files.length) activate(0);
  }

  function renderRun() {
    byId('run').innerHTML = `
      <h2>运行方式</h2>
      ${li(data.run)}
      <p class="note">如果仅浏览网站，也可直接用浏览器打开 <code>web/review/index.html</code>。</p>
    `;
  }

  function renderProgress() {
    byId('progress').innerHTML = `
      <h2>项目进度 / 完成情况</h2>
      ${li(data.progress.done.map((x) => `<span class="ok">✔</span> ${x}`))}
      <h3>待补充</h3>
      ${li(data.progress.todo.map((x) => `<span class="warn">◻</span> ${x}`))}
    `;
  }

  function renderRoadmap() {
    byId('roadmap').innerHTML = `
      <h2>后续优化方向</h2>
      ${li(data.roadmap)}
    `;
  }

  function renderLimits() {
    byId('limits').innerHTML = `
      <h2>当前已有能力与限制</h2>
      <h3>已有能力</h3>
      ${li(data.capabilities)}
      <h3>限制</h3>
      ${li(data.limitations)}
    `;
  }

  renderHero();
  renderOverview();
  renderFeatures();
  renderArchitecture();
  renderTree();
  renderCode();
  renderRun();
  renderProgress();
  renderRoadmap();
  renderLimits();
})();
