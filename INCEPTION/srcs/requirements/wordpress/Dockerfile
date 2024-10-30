#syntax=docker/dockerfile:1
FROM alpine:3.19 AS wordpress
ARG	WP_PHAR VS WP_CONF WP_CLI_CONFIG_PATH WP_INIT
ENV	WP_CLI_CONFIG_PATH=${WP_CLI_CONFIG_PATH} VS=${VS}
RUN apk update && apk add curl php${VS} php${VS}-phar php${VS}-curl php${VS}-openssl\
	php${VS}-mysqli php${VS}-mbstring php${VS}-fpm
COPY ${WP_CONF} /etc/wp-cli.yml
COPY ${WP_INIT} /usr/local/bin/init_wp.sh
RUN --mount=type=secret,id=mariadb_admin_key,env=ADMN_KEY\
	--mount=type=secret,id=mariadb_wdprss_key,env=WDPRSS_KEY\
	sed -i -e "{/WP_KEY/s//${WDPRSS_KEY}/;/ADMN_KEY/s//${ADMN_KEY}/}" \
	/usr/local/bin/init_wp.sh
RUN	sed -i -e '/listen.*9000/s/127.0.0.1/wordpress/' /etc/php${VS}/php-fpm.d/www.conf
RUN	chmod +x /usr/local/bin/init_wp.sh
RUN curl -O ${WP_PHAR} && php wp-cli.phar --info
RUN	chmod +x wp-cli.phar && mv wp-cli.phar /usr/local/bin/wp
RUN	wp core download 
ENTRYPOINT ["/usr/local/bin/init_wp.sh"]

