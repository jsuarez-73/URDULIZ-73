# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsuarez- <jsuarez-@student.42urduliz.co>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 10:40:31 by jsuarez-          #+#    #+#              #
#    Updated: 2024/10/24 16:07:49 by jsuarez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include srcs/.env

DEPENDENCY=$(addprefix $(MK_CTX), $(NGINX_CERT))

all: $(NGINX_)
	docker compose -f srcs/docker-compose.yml up

$(NGINX_): $(DEPENDENCY)

$(DEPENDENCY):
	#Create the certificate x509 without PEM password (noenc) and with the subjects
	#CN=domain_name, encriptation-algorithm=rsa and digest-signing sha512 (take the
	#public key signed and make it 512 bytes long from sha-algorithm (hash function)
	openssl req -x509 -sha512 -newkey rsa:4096 -noenc \
		-keyout $(MK_CTX)$(CERT_KEY) -out $(MK_CTX)$(CERT_) \
		-subj "/C=ES/ST=Bizkaia/L=Galdakao/CN=localhost/"
	chmod 755 $(MK_CTX)$(NGINX_CONF)

.PHONY: all $(NGINX_)
