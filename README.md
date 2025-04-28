此代码仓库为[wty-yy's blog - Effective Modern C++笔记](https://wty-yy.xyz/posts/33835/)样例

## VsCode配置
在`tasks.json`文件中加入
```json
"args": [
    "-fdiagnostics-color=always",
    "-I", "${workspaceFolder}",  // 这一行, 来找到my_show_type.hpp头文件
    "-g",
    "${file}",
    "-o",
    "${fileDirname}/${fileBasenameNoExtension}"
],
```