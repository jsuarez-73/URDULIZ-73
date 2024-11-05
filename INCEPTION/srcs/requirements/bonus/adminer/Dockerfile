FROM alpine:3.19 AS adminer
ARG VS
RUN apk update && apk add curl php${VS} php${VS}-phar php${VS}-curl php${VS}-openssl\
	php${VS}-mysqli php${VS}-mbstring php${VS}-fpm php${VS}-ctype php${VS}-redis \
	php${VS}-ftp
RUN	mkdir -p /var/www/adminer/
RUN curl -L "https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1-mysql.php" -o /var/www/adminer/index.php
EXPOSE 8080
ENTRYPOINT	["php"]
CMD	["-S", "[::]:8080", "-t", "/var/www/"]

