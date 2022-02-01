
## install hadoop

download hadoop in apache.
set environments:

```
export HADOOP_HOME=hadoop_path
export PATH=%HADOOP_HOME%/bin;%HADOOP_HOME%/sbin
```

(in windows) change `etc/hadoop/hadoop-env.cmd` file:

```
# use PROGRA~1 instead of Program files in windows.
set JAVA_HOME=C:\ProGRA~1\Java\jdk-12.0.1
```

```
hadoop version
```

working with hive.
```
hdfs dfs -chmod -R 777 /
```

//http://192.168.6.144:50070/
//http://192.168.6.144:8088/