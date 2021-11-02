## Change notebook working dir

Open "jupyter_notebook_config" file in ${User_dir}/.jupyter dir.

set c.NotebookApp.notebook_dir to whatever you what and remeber to remove '#' at the beginning of the line.

## set anaconda source

open anaconda cmd

``` cmd
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn
conda config --set show_channel_urls yes
conda config --remove-key channels
```
