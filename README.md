此代码仓库为[wty-yy's blog - Effective Modern C++笔记](https://wty-yy.xyz/posts/33835/)样例

## VsCode配置
先按F5自动生成配置文件`.vscode/tasks.json`

在`tasks.json`文件中修改
```json
"args": [
    "-fdiagnostics-color=always",
    "-I", "${workspaceFolder}",  // 这一行, 来找到my_show_type.hpp
    "-I", "${fileDirname}",  // 这一行, 找到统计目录下可能存在的*.hpp
    "-g",
    "${file}",
    "-o",
    "${workspaceFolder}/bin/${fileBasenameNoExtension}"  // 修改生成的可执行文件路径到bin文件夹下
],
```