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

## git 删除提交，但不删除文件：
```
git remove --cached filename
```


## git 删除文件夹，包括历史记录
```
git filter-branch --index-filter "git rm -rf --cached --ignore-unmatch path_to_file" HEAD
```

## push by token
```cmd 
git push https://YOUR_TOKEN@github.com/ProfFL028/TwilightStruggle
```

## what did I push?

```cmd
git show 
git log -nl -p
```

## How to rewrite commit message?
```cmd
git commit --amend --only -m "new message"
```

## How to change username and email in current commit?
```
git commit --amend --author "new username username@useremail.com"
```

## How to remove a file from commit
```
git checkout HEAD^ myfile
git add -A
git commit --amend
```

## How to delete last commit?
```
// dangerous!!!!
git reset HEAD^ --hard
git push -f remote branch
// if you didn't push yet
git reset --soft HEAD@{1}

// safeway if you've pushed to server
git revert SHAofBadCommit
git push -f
```

## How to delete historical commit?
```
// dangerous!!!!
git rebase --onto SHA1_OF_BAD_COMMIT^ SHA1_OF_BAD_COMMIT
git push -f remote branch
```

## How to rollback after hard reset
```
git reflog
git reset reset --hard SHA1234
```

## How to stage part instead of whole file>
```
git add --patch filename.x
// if filename.x isnot created 
git add -N filename.x
// s option help separate commit and e option will tell git which rows will commit.
git diff --cached // show staged lines in local file system
```

## How to commit changes to two and more commit 
```
git add -p 
```

## how to swap staged and unstaged status?
```
git add .
git stash
git reset HEAD^
git stash pop --index 0
```

## How to move unstaged files to a new branch
```
git checkout -b my-branch
```

## How to move unstaged files to an existing branch
```
git stash
git checkout my-branch
git stash pop
```

## How to reset uncommitted changes
```
git reset --hard HEAD^
# two commits
git reset --hard HEAD^^
# four commits
git reset --hard HEAD^4
# or
git checkout -f
# specific file
git reset filename
```

## delete some unstaged files
```
git checkout -p
# or
git stash -p
git reset --hard
git stash pop
# or
git stash -p
git stash drop
```

## How to reset branch to desired commit?
```
git reflog
git reset --hard SHA
```

## How to drop local commit and async with remote branch?
```
git status 
git reset --hard origin/my-branch
```

## I want to commit to a new branch but committed to main branch, how to fix it ?
```
git branch my-branch 
git reset --hard HEAD^
git checkout my-branch
```

## How to reserve `ref-ish`
```
git add -A && git commit -m "add whole files"
(develop) $ git checkout solution --file1.txt
(develop) $ git commit -m "file1.txt"
```

## How to commit from different branches to main branch?
```
git log
# e3851e8 bug #21 fix
# 5ea5173 bug #14 fix
# a13b85e main 

git reset --hard a13b85e
git checkout -b 21
git cherry-pick e3851e8
// fix conflicts in git repository
git checkout main
git checkout -b 14
git cherry-pick 5ea5173
```

## mis delete local branch instead of upstream branch
```
git fetch -p
```

## mis delete branch
```
# operation repick
git checkout -b my-branch
git branch
touch foo.txt
ls
git add .
git commit -m "foo.txt added"
git checkout main
git branch -D my-branch

# fix
git reflog
git checkout -b my-branch-help
git reset --hard 4e3cd85(HEAD^^)
ls
```

## delete a remote branch
```
git push origin --delete my-branch
# local
git branch -D my-branch
```

## checkout a branch from other's working branch
```
git fetch --all
git checkout --track origin/daves
```

## rollback rebase/merge
```
git reset --hard ORIG_HEAD
```

## do not use `force push` after rebase
```
git checkout my-branch
git rebase -i main
git checkout main
git merge --ff-only my-branch
```

## How to combine some commit
```
git reset --soft main
git commit -am "New awesome features"
# keep timestamp
git rebase -i main
# combine latest two commits
git rebase -i HEAD~2
```

## safe merging strategy
```
git merge --no-ff --no-commit my-branch
```

## merge a branch to commit
```
git merge --squash my-branch
```

## combine unpushed commit only
```
git rebase -i @{u}
```

## check if all commit are merged
```
git log --graph --left-right --cherry-pick --oneline HEAD...feature/120-on-scroll
# or
git log main ^feature/120-on-scroll --no-merges
```

## visual diff editor
```
git mergetool -t opendiff
git rebase --continue
git rebase --abort/ git rebase --skip
```

## stash working dir
```
git stash
# exclude some files
git stash -u 
```

## stash some file
```
git stash push working-path/file.txt
```

## add messages when stashing
```
git stash save <message>
git stash list
```

## store unstashed commit when stash
```
git stash create
git stash store -m "commit-message CREATED_SHA1
```

## clone all modules
```
git clone --recursive git://github.com/foo/bat.git
# already cloned
git submodule update --init --recursive
```

## delete tag
```
git tag -d <tag_name>
git push <remote> :refs/tags/<tag_name>
```

## recover deleted tag
```
git fsck --unreachable | grep tag # get tag
git update-ref refs/tags/<tag_name> <hash>
```

## cap uncap filename 
```
git mv --force myfile MyFile
```

## delete a file in git but leave it in local
```
git rm --cached log.txt
```

