FROM alpine:3.19 AS ttyd
RUN	apk update && apk add curl git
RUN	apk add nodejs npm
RUN git clone https://github.com/louislam/uptime-kuma.git
WORKDIR uptime-kuma
RUN npm run setup
ENTRYPOINT ["node"]
CMD ["server/server.js"]
