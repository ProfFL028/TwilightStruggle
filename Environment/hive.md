# Hive Basic

## how to install Hive?

make sure `hadoop` and `mysql` are installed and started.

```shell
jps
```

it should output in master: `SecondaryNameNode NameNode Jps ResourceManager` and `Jps NodeManager DataNode` in slave nodes

1. unzip `apache-hive-<version>-bin.tar.gz` to /opt dir and set chmod to 777
2. `cd /opt/apache-hive-2.3.9-bin/scripts/metastore/upgrade/mysql`  
3. exec `hive-schema-<version>-mysql.sql` in mysql if your mysql version does not in the list, choose any.

## How to start Hive ?

1. `cd /opt/apache-hive-<version>-bin/bin`
2. `./hive`

## hive-site.xml

tell hive where metastore database is and how to connect to it.

```xml
<?xml version="1.0"?>
<?xml-stylesheet type="text/xsl" href="configuration.xsl"?>
<configuration>
  <property>
    <name>hive.metastore.local</name>
    <value>true</value>
  </property>

  <property>
    <name>javax.jdo.option.ConnectionURL</name>
    <value>jdbc:mysql://master:3306/hive?createDatabaseIfNotExist=true</value>
  </property>

  <property>
    <name>javax.jdo.option.ConnectionDriverName</name>
    <value>com.mysql.jdbc.Driver</value>
  </property>

  <property>
    <name>javax.jdo.option.ConnectionUserName</name>
    <value>hadoop</value>
  </property>
  <property>
    <name>javax.jdo.option.ConnectionPassword</name>
    <value>123456</value>
  </property>
</configuration>
```

## hive --help

```shell
[hadoop@localhost bin]$ ./hive --help
Usage ./hive <parameters> --service serviceName <service parameters>
Service List: beeline cleardanglingscratchdir cli hbaseimport hbaseschematool help hiveburninclient hiveserver2 hplsql jar lineage llapdump llap llapstatus metastore metatool orcfiledump rcfilecat schemaTool version 
Parameters parsed:
  --auxpath : Auxiliary jars 
  --config : Hive configuration directory
  --service : Starts specific service/component. cli is default
Parameters used:
  HADOOP_HOME or HADOOP_PREFIX : Hadoop install directory
  HIVE_OPT : Hive options
For help on a particular service:
  ./hive --service serviceName --help
```

### hive --service serviceName

|  options | Description  |
|:---|:---|
|  cli  | default service, |
|hiveserver|a daemon process listening  thrift connections from other process|
|hwi|a simple web gui interface for executing queries and other commands|
|jar|extends for `haddop jar`|
|metastore|start an extended metadata hive service|
|rcfilecat|print RCFile format|
|||

### hive --service cli --help

```shell
usage: hive
 -d,--define <key=value>          Variable substitution to apply to Hive
                                  commands. e.g. -d A=B or --define A=B
    --database <databasename>     Specify the database to use
 -e <quoted-query-string>         SQL from command line
 -f <filename>                    SQL from files
 -H,--help                        Print help information
    --hiveconf <property=value>   Use value for given property
    --hivevar <key=value>         Variable substitution to apply to Hive
                                  commands. e.g. --hivevar A=B
 -i <filename>                    Initialization SQL file
 -S,--silent                      Silent mode in interactive shell
 -v,--verbose                     Verbose mode (echo executed SQL to the
                                  console)

```

#### hive variables

|namespace|priviledge|description|
|:---|:---|:---|
|hivevar|rw|user defined|
|hiveconf|rw| hive config|
|system|rw|java config|
|env|r|bash envrionment|
||||

usage:

```shell
# using hivevar
set hivevar:foo=bar2;
create table toss1(i int, ${hivevar:foo} string);
describe toss1;
drop table toss1;

#using hiveconf
hive --hiveconf hive.cli.print.current.db=true
set hiveconf:hive.cli.print.current.db=false;

hive --hiveconf y=5
create table whatsit(i int);
select * from whatsit where i=${hiveconf:y}

#using system
set system:user.name=yourname;

#read env (as we can't write it)
set env:HOME
```

#### hive once-only commands

```shell
hive -e "select * from mytable limit 3";

hive -f /path/to/file/withqueries.hql 
# in hive cli
source /path/to/file/withqueies.hql;
```

## hiverc

```text
ADD JAR /path/to/custom_hive_extensions.jar
set hive.cli.print.current.db=true
set hive.exec.mode.local.auto=true
```

## hive data types

|data type| length|
|:---|:---|
|TINYINT|1 byte signed integer|
|SMALLINT|2 byte signed integer|
|INT|4 byte signed integer|
|BIGINT|8 byte signed integer|
|BOOLEAN|true, false|
|FLOAT|single precision float|
|DOUBLE| double precision float|
|STRING|string|
|TIMESTAMP|integer: (start from 1970.01.01:00:00:00), same to java.sql.Timestamp|
|BINARY|binary array|
|STRUCT|struct('John', 'Doe')|
|MAP|map('first', 'John', 'last', 'Doe')|
|ARRAY|Array('John', 'Doe')|
|||

```sql
CREATE TABLE employees(
    name          STRING,
    salary        FLOAT,
    subordinates  ARRAY<STRING>,
    deductions    MAP<STRING, FLOAT>,
    address       STRUCT<street:STRING, city:STRING, state:STRING, zip:INT> 
);
```

## textfile encoding

|seperate code|description|
|:---|:---|
|\n|line seperate|
|^A|column(field) seperate(\001)|
|^B|ARRAY, STRUCT, MAP seperate(\002)|
|^C|MAP seperate(\003)|
|||

```sql
CREATE TABLE employees(
    name          STRING,
    salary        FLOAT,
    subordinates  ARRAY<STRING>,
    deductions    MAP<STRING, FLOAT>,
    address       STRUCT<street:STRING, city:STRING, state:STRING, zip:INT> 
)
ROW FORMAT DELIMITED
FIELDS TERMINATED BY '\001'
COLLECTION ITEMS TERMINATED BY '\002'
MAP KEYS TERMINATED BY '\003'
LINES TERMINATED BY '\n'
STORED AS TEXTFILE;
```
