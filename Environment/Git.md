## How to use token in github:

Login to github, in profiles->settings->Developer settings->Personal access token
generate a new token, copy the token before close the page !!!!!!
For simplity we can use git remote command:

```
git remote set-url origin https://<TOKEN>@github.com/<USERNAME>/<REPOSITORY>.git
```

After running the above code, we can now push code to github.