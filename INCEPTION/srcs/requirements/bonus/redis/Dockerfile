# syntax=docker/dockerfile:1
FROM alpine:3.19 AS redis
RUN	apk update && apk add redis
RUN	sed -i -e '{/^bind.*$/s/127.*$/* -::*/;/^protected-mode.*$/s/yes/no/;}' \
	/etc/redis.conf
EXPOSE 6379
ENTRYPOINT ["redis-server"]
CMD ["/etc/redis.conf"]
