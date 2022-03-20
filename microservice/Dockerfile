FROM openjdk:11-jre-slim
LABEL maintainer=profFL
WORKDIR /app
COPY libs libs/
COPY classes classes/
ENTRYPOINT ["java", "-cp", "/app/resources:/app/classes:/app/libs/*", "me/proffl/microservice/MicroserviceApplication"]
EXPOSE 8080