# Kafka Streams and ksqlDB

## How to start a kafka producer in docker?

```shell
docker-compose up
docker-compose exec kafka bash
kafka-console-producer --bootstrap-server localhost:9092 --topic users
```

## How to build a kafka project?

```gradle
// needs to add following repository in repositories:
maven {
    url "https://packages.confluent.io/maven/"
}
implementation "org.apache.kafka:kafka-streams:${kafkaVersion}"
implementation ('io.confluent:kafka-streams-avro-serde:6.0.1') {
    exclude group: 'org.apache.kafka', module: 'kafka-clients'
}
```

## How to start listening to a kafka producer?

```kotlin
// method 1: using original stream
val builder = StreamsBuilder()
val stream = builder.stream<Void, String>("topic-name")
stream.foreach { _, value -> process(value) }

val streams = KafkaStreams.build(builder, config)
streams.start()

Runtime.getRuntime().addShutdownHook(Thread(streams::close))

// method 2: using topology
val topology = Topology()
topology.addSource("UserSource", "users")
topology.addProcessor("SayHello", ProcessorSupplier { SayHelloProcessor() }, "UserSource")

val streams = KafkaStreams(topology, KafkaUtil.getDefaultConfig())
streams.start()
Runtime.getRuntime().addShutdownHook(Thread(streams::close))
```

## Failed to rebalance error in Kafka Streams with more than one topic partition

add data to kafka source would fix the problem.
