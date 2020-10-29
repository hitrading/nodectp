# warning
目前仅支持linux64和win64平台(win32平台未测试，理论上支持)

支持的nodejs版本: 8.x.x, 如: 8.16.1  ***(8以上版本不被支持)***

# compile
windows平台需要安装编译工具：`npm install --global --production windows-build-tools`

执行脚本：
```
npm run rebuild 或 yarn rebuild
```

# execute
run example
```
node ./example/ctpapp.js
```

# Example
请参看[example](https://github.com/iamweilee/nodectp-example.git)

# version
适配看穿式监管库, 实配的库版本: 6.3.15_20190220、v6.3.15_P2_mdapi_se_20190403 (实现了ctp所有的接口, 其中包含客户端认证及组播接口)

### 可能遇到的报错问题
执行 `yarn build` 命令时可能会遇到node.lib文件损坏的情况, 此时可去官网下载node.lib文件替换, 下载地址：[https://nodejs.org/dist/latest-v8.x/win-x64/node.lib]


### 适配Nan

参考 https://github.com/octalmage/robotjs/pull/523/files
