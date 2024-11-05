# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 10:40:31 by jsuarez-          #+#    #+#              #
#    Updated: 2024/10/24 18:03:06 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include srcs/.env

DEPENDENCY=$(addprefix $(MK_CTX), $(NGINX_CERT))

all: $(NGINX_)
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=0/' srcs/.env
	mkdir -p ${DB_DIR}
	mkdir -p ${WP_DIR}
	mkdir -p ${WEB_DIR}
	docker compose -f srcs/docker-compose.yml --profile all up

bonus: $(NGINX_)
	mkdir -p ${DB_DIR}
	mkdir -p ${WP_DIR}
	mkdir -p ${WEB_DIR}
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=1/' srcs/.env
	docker compose -f srcs/docker-compose.yml -f ${MK_DIR_BONUS}/docker-compose.yml \
		--profile ttyd --profile adminer --profile web --profile redis --profile ftp \
		--profile all up
redis:
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=1/' srcs/.env
	docker compose -f srcs/docker-compose.yml -f ${MK_DIR_BONUS}/docker-compose.yml \
		--profile redis up
ftp:
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=1/' srcs/.env
	docker compose -f srcs/docker-compose.yml -f ${MK_DIR_BONUS}/docker-compose.yml \
		--profile ftp up
web:
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=1/' srcs/.env
	docker compose -f srcs/docker-compose.yml -f ${MK_DIR_BONUS}/docker-compose.yml \
		--profile web up
adminer:
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=1/' srcs/.env
	docker compose -f srcs/docker-compose.yml -f ${MK_DIR_BONUS}/docker-compose.yml \
		--profile adminer up
ttyd:
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=1/' srcs/.env
	docker compose -f srcs/docker-compose.yml -f ${MK_DIR_BONUS}/docker-compose.yml \
		--profile ttyd up

web_ngnx: $(DEPENDENCY)
	mkdir -p ${DB_DIR}
	mkdir -p ${WP_DIR}
	mkdir -p ${WEB_DIR}
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=1/' srcs/.env
	docker compose -f srcs/docker-compose.yml -f ${MK_DIR_BONUS}/docker-compose.yml \
		--profile web --profile redis --profile ftp --profile all up

wordpress:
	mkdir -p ${WP_DIR}
	docker compose -f srcs/docker-compose.yml --profile wordpress up

mariadb:
	mkdir -p ${DB_DIR}
	docker compose -f srcs/docker-compose.yml --profile mariadb up

mdb_wp:
	mkdir -p ${DB_DIR}
	mkdir -p ${WP_DIR}
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=1/' srcs/.env
	docker compose -f srcs/docker-compose.yml --profile mariadb --profile wordpress up

ngnx_mdb: $(DEPENDENCY)
	mkdir -p ${DB_DIR}
	docker compose -f srcs/docker-compose.yml --profile mariadb --profile nginx up

ngnx: $(DEPENDENCY)
	mkdir -p ${WP_DIR}
	docker compose -f srcs/docker-compose.yml --profile nginx up

$(NGINX_): $(DEPENDENCY)

$(DEPENDENCY):
	#Create the certificate x509 without PEM password (noenc) and with the subjects
	#CN=domain_name, encriptation-algorithm=rsa and digest-signing sha512 (take the
	#public key signed and make it 512 bytes long from sha-algorithm (hash function)
	openssl req -x509 -sha512 -newkey rsa:4096 -noenc \
		-keyout $(MK_CTX)$(CERT_KEY) -out $(MK_CTX)$(CERT_) \
		-subj "/C=ES/ST=Bizkaia/L=Galdakao/CN=localhost/"
	chmod 755 $(MK_CTX)$(NGINX_CONF)

fclean:
	rm -rf $(MK_CTX)$(CERT_KEY) $(MK_CTX)$(CERT_)
	dprune
	docker volume rm -f inception_db

.PHONY: all $(NGINX_) mariadb wordpress mdb_wp ngnx_mdb ngnx bonus redis ftp wp_bonus web web_ngnx \
	adminer
