## How to use token in github:

Login to github, in profiles->settings->Developer settings->Personal access token
generate a new token, copy the token before close the page !!!!!!
For simplity we can use git remote command:

```
git remote set-url origin https://<TOKEN>@github.com/<USERNAME>/<REPOSITORY>.git
```

After running the above code, we can now push code to github.

## git 拒绝合并无关历史：
```
git pull origin main --allow-unrelated-histories
```

## git 删除文件夹，包括历史记录
```
git filter-branch --index-filter "git rm -rf --cached --ignore-unmatch path_to_file" HEAD
```

## push by token
```cmd 
git push https://YOUR_TOKEN@github.com/ProfFL028/TwilightStruggle
```
