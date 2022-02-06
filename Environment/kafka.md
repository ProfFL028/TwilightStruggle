# how to start kafka server?
```
cd /opt/kafka-[tab]
bin/zookeeper-server-start.sh config/zookeeper.properties
bin/kafka-server-start.sh config/server.properties
```

# How to start a kafka topic?
```
bin/kafka-topics.sh --create --topic <topic-name> --bootstrap-server localhost:9092 --replication-factor 1 --partitions 1
```

# Show all topics
```
bin/kafka-topics.sh --list --bootstrap-server localhost:9092
```

# create producer
```
bin/kafka-console-producer.sh --topic <topic-name> --bootstrap-server localhost:9092
```

# create consumer
```
bin/kafka-console-consumer.sh --topic <topic-name> --bootstrap-server localhost:9092
```
