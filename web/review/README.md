# web/review

仓库可视化审阅网站。

## 启动

```bash
cd /home/runner/work/review/review
python -m http.server 8000
```

打开：`http://127.0.0.1:8000/web/review/index.html`

## 数据更新

当仓库内容变化后，重新生成数据：

```bash
python /home/runner/work/review/review/web/review/generate_data.py
```
