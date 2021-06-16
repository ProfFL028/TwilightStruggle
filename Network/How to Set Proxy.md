## How to Set Proxy in VS Code
文件->首选项->设置  
弹出窗口中 搜索"http proxy"，在输入框中输入相应的代理地址 (例如：https://127.0.0.1:58591)

## How to Set Proxy in CMD
```
// replace `set` with `export` when using mac/linux
set http_proxy=http://127.0.0.1:58591
set https_proxy=https://127.0.0.1:58591
// test if proxy settings works using `curl` command instead of `ping`
curl www.google.com
```

## How to Set Proxy in Intellij IDEA
1.File->Settings  
2.Searching for `proxy`  
3.In the popup window,  check `Manual proxy configuration`  
4.Modify `Host name` and `port number` to your proxy url.

## How to Set Proxy in Github CMD
```
git config --global http.proxy http://127.0.0.1:58591
```
