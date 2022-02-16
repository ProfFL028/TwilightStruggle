## 公司怎么提交的实时任务，有多少Job Manager？
提交都会创建一个新的Flink集群，为每个job提供一个yarn-session，任务之间互相独立，互不影响，方便管理。任务执行完成之后创建的集群也会消失。(作业模式)
```
$ bin/yarn-session.sh -n 7 -s 8 -jm 3072 -tm 32768 -qu root.*.*-nm *-* -d
```
其中申请7个taskManager，每个8核，每个taskmanager有32768M内存。
集群默认只有一个Job Manager。但为了防止单点故障，一般配置一个主Job Manager，两个备用Job Manager，然后结合ZooKeeper的使用，来达到高可用。

## 怎么做压力测试和监控
一般碰到的压力来自以下几个方面：

一，产生数据流的速度如果过快，而下游的算子消费不过来的话，会产生背压问题。背压的监控可以使用Flink Web UI(localhost:8081)来可视化监控，一旦报警就能知道。一般情况下背压问题的产生可能是由于sink这个操作符没有优化好，做一下优化就可以了。比如如果是写入ElasticSearch，那么可以改成批量写入，可以调大ElasticSearch队列的大小等等策略。

二，设置水位线的最大延迟时间这个参数，如果设置的过大，可能会造成内存的压力。可以设置的最大延迟时间小一些，然后把迟到元素发送到侧输出流中去。晚一点更新结果。或者使用类似于RocksDB这样的状态后端，RocksDB会开辟堆外存储空间，但IO速度会变慢，需要权衡。

三，还有就是滑动窗口的长度如果过长，而滑动距离很短的话，Flink的性能会下降的很厉害。

四，状态后端使用RocksDB，还没有碰到被撑爆的问题。

五，尽量使用滚动窗口，这样会大大减轻存储的压力。

六，如果想要达到极限的低延迟，可以考虑使用处理时间（Processing Time）。

七，业务逻辑的编写是最重要的。在算子中（例如processElement, onTimer）业务逻辑一定要尽可能的简单，而不是特别复杂的业务逻辑（举个极端的例子，机器学习这种CPU密集型的程序，十几张表的Join）。如果业务逻辑很复杂的话，将会阻塞数据流的向下传递。性能会急剧下降。

## 为什么使用Flink替代Spark？
一，Flink是真正的流处理，延迟在毫秒级，Spark Streaming是微批，延迟在秒级。

二，Flink可以处理事件时间，而Spark Streaming只能处理机器时间，无法保证时间语义的正确性。

三，Flink的检查点算法比Spark Streaming更加灵活，性能更高。Spark Streaming的检查点算法是在每个stage结束以后，才会保存检查点。

四，Flink易于实现端到端一致性。

## Flink的CheckPoint存在哪里
状态后端。内存，文件系统，或者RocksDB。

## 如果下级存储不支持事务，Flink怎么保证exactly-once？
幂等性写入(Redis, ElasticSearch)。

## 说一下Flink状态机制
流处理程序内部的一致性，端到端一致性。

## 怎么去重？考虑一个实时场景：双十一场景，滑动窗口长度为1小时，滑动距离为10秒钟，亿级用户，计算UV？
布隆过滤器（Bloom Filter）、位图

## Flink的checkpoint机制对比spark有什么不同和优势？

spark streaming的Checkpoint仅仅是针对driver的故障恢复做了数据和元数据的Checkpoint。而flink的checkpoint机制要复杂了很多，它采用的是轻量级的分布式快照，实现了每个操作符的快照，及循环流的在循环的数据的快照。
（https://cloud.tencent.com/developer/article/1189624）

## Flink的Watermark详细说明


## Flink ExactlyOnce语义是如何实现的，状态是如何存储的
一，Flink应用程序内部的exactly-once

二，端到端一致性

## Flink CEP编程中当状态没有到达的时候会将数据保存在哪里？

CEP当然在流式处理中是要支持EventTime的，那么相对应的要支持数据的晚到现象，也就是watermark的处理逻辑。在Flink的处理逻辑中，将晚到数据明细存储在了Map<Long, List>的结构中，也就是说，如果watermark设置为当前时间减去5分钟，那么内存中就会存储5分钟的数据。

## Flink三种时间概念分别说出应用场景
Event Time：

Processing Time：没有事件时间的情况下，或者对实时性要求超高的情况下。

Ingestion Time：存在多个Source Operator的情况下，每个Source Operator会使用自己本地系统时钟指派Ingestion Time。后续基于时间相关的各种操作，都会使用数据记录中的Ingestion Time。

## Flink程序在面对数据高峰期时如何处理
1，使用大容量的Kafka把数据先放到消息队列里面。再使用Flink进行消费，不过这样会影响到一点实时性。

2，使用滚动窗口

3，使用处理时间

4，下游使用消费速度快的外围设备（如Kafka）

## flink消费kakfa保证数据不丢失（flink消费kafka数据不丢不重，flink消费kafka的时候挂了怎么恢复数据）

端到端一致性（exactly-once），flink会维护消费kafka的偏移量，checkpoint操作。

## Flink过来的数据量太大怎么处理
加机器，考虑使用处理时间（ProcessingTime），前面使用Kafka来做蓄水池，降低消费数据的速度。尽量使用滚动窗口，窗口没有重合，数据不会复制到不同的窗口中去。

## Kafka每5分钟过来的数据量是多少，flink跑的实时频率，flink topN 跑的频率
一天数据量是100万，所以我们的窗口大小一般设置为1小时，所以数据量大约在10万条左右。

## Flink的资源是如何设置的，设置资源的时候依据是什么？

记录数和每条记录的大小
确定集群大小的首要事情就是估算预期进入流计算系统的每秒记录数（也就是我们常说的吞吐量），以及每条记录的大小。不同的记录类型会有不同的大小，这将最终影响 Flink 应用程序平稳运行所需的资源。

不同 key 的数量和每个 key 存储的 state 大小
应用程序中不同 key 的数量和每个 key 所需要存储的 state 大小，都将影响到 Flink 应用程序所需的资源，从而能高效地运行，避免任何反压。

状态的更新频率和状态后端的访问模式
第三个考虑因素是状态的更新频率，因为状态的更新通常是一个高消耗的动作。而不同的状态后端（如 RocksDB，Java Heap）的访问模式差异很大，RocksDB 的每次读取和更新都会涉及序列化和反序列化以及 JNI 操作，而 Java Heap 的状态后端不支持增量 checkpoint，导致大状态场景需要每次持久化的数据量较大。这些因素都会显著地影响集群的大小和 Flink 作业所需的资源。

网络容量
网络容量不仅仅会受到 Flink 应用程序本身的影响，也会受到可能正在交互的 Kafka、HDFS 等外部服务的影响。这些外部服务可能会导致额外的网络流量。例如，启用 replication 可能会在网络的消息 broker 之间产生额外的流量。

磁盘带宽
如果你的应用程序依赖了基于磁盘的状态后端，如 RocksDB，或者考虑使用 Kafka 或 HDFS，那么磁盘的带宽也需要纳入考虑。

机器数量及其可用 CPU 和内存
最后但并非最不重要的，在开始应用部署前，你需要考虑集群中可用机器的数量及其可用的 CPU 和内存。这最终确保了在将应用程序投入生产之后，集群有充足的处理能力。


##Flink上有多少个指标，一个指标一个jar包吗？Flink亲自负责的有几个jar包产出？

## flink的开发中用了哪些算子？

## flink的异步join有了解吗？就是例如kafka和MySQL的流进行join

## flink的broadcast join的原理是什么？

## flink的双流join你们用的时候是类似数据中的left join还是inner join，双流join中怎么确定左表还是右表【没太懂，好像应该是full join，全外连接】，CoProcessFunction是全外连接，基于间隔的Join和基于窗口的Join是Inner Join

## flink集群有多大，怎么部署的？

## hadoop集群有多大，分给flink有多少资源，多少cpu，多少内存，多少slot？

## 你自己写的哪些jar包，用了多少cpu，用了内存，多少个slot？
## 有没有关注你的jar包的处理性能，就是处理kafka的qps和tps？

## 你们有用过flink的背压吗，怎么做优化还是调整？
## flink的知识点还有啥想介绍的？

## flink如何实现精准一次性？flink怎么保证容错性，说些checkPoint的内部原理，要很细节的。
## flink的双流join有什么问题？写代码实现interval join的功能，怎么实现？
## 通过双流join进行对账，有没有没join上的情况，interval join的时间是多少，你设置这个时间不会有数据丢失？

## flink输出的目标数据库是什么
自定义mysqlsink，sink里面实际上是jdbc做的。一般不直接写入mysql，因为jdbc批写入的性能一般不够好，先写入到kafka，再通过kafka消费写入到mysql
