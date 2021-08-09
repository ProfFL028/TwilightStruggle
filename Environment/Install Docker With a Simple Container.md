# Install Docker With a Simple Container

## 1. Install Docker 
Install Docker which can be downloaded in [docker](https://www.docker.com/get-started). If your computer have installed wsl, you need to update it to [wsl2](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi)

## 2. Prepare Project

It just make a directory for the project and add some basic files in it.

```shell
mkdir docker_web
cd docker_web
touch Dockerfile
mkdir src
touch src/index.py
```

Install flask using pipenv(check net connection), and wirte Pipfile.

```shell
pipenv install flask
```

Write Hello World in [index.py](doc_web/src/index.py)

Test if it works correctly. Your need to call "pipenv shell" to active pipenv if using it.

```shell
pipenv shell 
python src/index.py
```

Write [Dockerfile](dock_web/Dockerfile) to package the project.

Build docker image and start it.

```shell
docker image build -t docker_web.v1

docer run -d -p 9876:5000 --name docker_web docker_web.v1
```

[The Page](http://localhost:9876) will show "Hi, Python" if everything is all right.