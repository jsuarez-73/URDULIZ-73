#syntax=docker/dockerfile:1
FROM alpine:3.19 AS web
ARG	DIR_WEB
RUN	apk update
RUN	apk add nodejs npm
RUN npm install -g @angular/cli
COPY ${DIR_WEB}/inception/ inception
WORKDIR	inception
RUN	npm install
RUN ng build --configuration production
ENTRYPOINT ["ng"]
CMD ["serve"]
