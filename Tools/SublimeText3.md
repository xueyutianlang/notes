# Sublime Text3

## 1. 配置

<table>
    <tr><th align="center">配置</th><th>配置项</th></tr>
    <tr><td align="center">字号</td><td>"font_size":12</td></tr>
    <tr><td align="center">高亮当前行</td><td>"highlight_line":true</td></tr>
    <tr><td align="center">显示当前编码</td><td>"show_encoding":true</td></tr>
    <tr><td align="center">Tab</td><td>"tab_size":4<br/>"translate_tabs_to_spaces":true</td></tr>
    <tr><td align="center">自动换行</td><td>"word_wrap":false</td></tr>
    <tr><td align="center">宽度指导线</td><td>"rulers":[80]</td></tr>
    <tr><td align="center">最后一行中间显示</td><td>"scroll_past_end":true</td></tr>
    <tr><td align="center">Vim 模式</td><td>"ignored_packages":["Vintage"]</td></tr>
    <tr><td align="center">显示空白符</td><td>"draw_white_space":"all"</td></tr>
    <tr><td align="center">显示全路径</td><td>"show_full_path":true</td></tr>
    <tr><td align="center">换行符</td><td>"default_line_ending":"unix"</td></tr>
</table>

### 1.1 参考资料

- [Sublime Text3 实用配置](https://segmentfault.com/a/1190000002596724)

## 2. 快捷键

### 2.1 搜索

- `Ctrl + F`：底部搜索框查找
- `Ctrl + Shift + F`：文件夹内查找
- `Ctrl + P`：打开搜索框
    - 打开文件：输入文件名
    - 跳转：`:数字`
- `Ctrl + G`：跳转，自动带`:`
- `Ctrl + R`：搜索函数，自动带`@`
- `Ctrl + :`：查找关键词，自动带`#`
- `Ctrl + Shift + P`：打开命令框
- `Esc`：退出

### 2.2 选择

- `Ctrl + D`：选中光标所占文本，继续操作则会选中下一个相同的文本
- `Alt + F3`：选中文本按下快捷键，即可一次性选择全部的相同文本进行同时编辑
- `Ctrl + L`：选中整行，继续操作则继续选择下一行
- `Ctrl + Shift + L`：先选中多行，再按下快捷键，会在每行行尾插入光标，即可同时编辑这些行
- `Ctrl + Shift + M`：选择括号内的内容（继续选择父括号）。如：快速选中删除函数中的代码，重写函数体代码或重写括号内里的内容
- `Ctrl + M`：光标移动至括号内结束或开始的位置
- `Ctrl + Enter`：在下一行插入新行
- `Ctrl + Shift + Enter`：在上一行插入新行
- `Ctrl + Shift + [`：选中代码，按下快捷键，折叠代码
- `Ctrl + Shift + ]`：选中代码，按下快捷键，展开代码
- `Ctrl + K + 0`：展开所有折叠代码
- `Ctrl + ←`：向左单位性地移动光标，快速移动光标
- `Ctrl + →`：向右单位性地移动光标，快速移动光标

### 参考资料

- [Sublime Text 相关集合](https://github.com/JaredCubilla/sublime)
