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
VOLUMES=${DB_DIR} ${WP_DIR} ${WEB_DIR}

all: $(DEPENDENCY) $(VOLUMES)
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=0/' srcs/.env
	docker compose -f srcs/docker-compose.yml --profile all up

bonus: $(DEPENDENCY) $(VOLUMES)
	sed -i -e '/^BONUS/s/BONUS.*/BONUS=1/' srcs/.env
	docker compose --env-file srcs/.env -f ${MK_DIR_BONUS}/docker-compose.yml \
		--profile bonus --profile all up
clean:
	docker compose -f ./srcs/docker-compose.yml down

re: clean
	docker compose -f srcs/docker-compose.yml up --build

fclean:
	rm -rf $(MK_CTX)$(CERT_KEY) $(MK_CTX)$(CERT_)
	docker stop $$(docker ps -qa); \
	docker rm $$(docker ps -qa); \
	docker rmi -f $$(docker images -qa); \
	docker volume rm $$(docker volume ls -q); \
	docker network rm $$(docker network ls -q) 2>/dev/null; \
	docker system prune --all --volumes -f; \
	sudo rm -rf ${VOLUMES_DIR}

$(DEPENDENCY):
	#Create the certificate x509 without PEM password (noenc) and with the subjects
	#CN=domain_name, encriptation-algorithm=rsa and digest-signing sha512 (take the
	#public key signed and make it 512 bytes long from sha-algorithm (hash function)
	openssl req -x509 -sha512 -newkey rsa:4096 -noenc \
		-keyout $(MK_CTX)$(CERT_KEY) -out $(MK_CTX)$(CERT_) \
		-subj "/C=ES/ST=Bizkaia/L=Galdakao/CN=localhost/"
	chmod 755 $(MK_CTX)$(NGINX_CONF)

$(VOLUMES):
	mkdir -p ${DB_DIR}
	mkdir -p ${WP_DIR}
	mkdir -p ${WEB_DIR}


.PHONY: all $(NGINX_) bonus fclean re clean
