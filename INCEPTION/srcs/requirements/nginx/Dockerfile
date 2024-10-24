# syntax=docker/dockerfile:1
FROM alpine:3.19 AS nginx
ARG PUBK_NAME
ARG PUBK_NGINX
ARG	NGINX_CONF
ARG	NGINX_CONF_NAME
ARG DIRKEY
ARG DIRCRT
ARG CERT_NAME
ARG	CERT_
ARG NGINX_DIR_DFLT_CONF
ARG	NGINX_DOMAIN_NAME
ARG	NGINX_DIRKEY
COPY ${PUBK_NGINX} /tmp/${PUBK_NAME}.org
#Update repositories registries and install nginx dependencies
RUN apk update && apk add openssl curl ca-certificates 
#Add to repositories looked by apk the mainline repository from nginx.
RUN printf "%s%s%s%s\n" "@nginx " \
	"http://nginx.org/packages/mainline/alpine/v" \ 
	$(egrep -o '^[0-9]+\.[0-9]+' /etc/alpine-release) "/main" \
	| tee -a /etc/apk/repositories
#Get the public key to verify the integrity from the download.
RUN curl -o /tmp/${PUBK_NAME} https://nginx.org/keys/${PUBK_NAME}
#Verify through openssl rsa the integrity of the nginx_signing_rsa.pub key
RUN openssl rsa -pubin -in /tmp/${PUBK_NAME} -text -noout | \
	diff - /tmp/${PUBK_NAME}.org
##Must be moved to apk keys folder to allow nginx installation from the space
#of @nginx repositories.
RUN mv /tmp/${PUBK_NAME} /etc/apk/keys/
#Install nginx
RUN apk add nginx@nginx
#Add certificate generated inside the container.
COPY ${CERT_} ${DIRCRT}
#Add our personal configuration to nginx.
COPY ${NGINX_DIR_DFLT_CONF} /etc/nginx/conf.d/${NGINX_CONF_NAME}
RUN	sed -i -e '/listen.*;$/a\' \
		-e "\\tserver_name ${NGINX_DOMAIN_NAME};\\n\
		\\tssl_certificate ${DIRCRT}/${CERT_NAME};\\n\
		\\tssl_certificate_key ${NGINX_DIRKEY};\\n" \
		/etc/nginx/conf.d/${NGINX_CONF_NAME}
#Add our certificate to the certificates trusted by Openssl
RUN	cat ${DIRCRT}/${CERT_NAME} >> \
	$(openssl version -d | egrep -o '/[^"]*')/cert.pem
RUN	--mount=type=secret,id=nginx_key\
	cp /run/secrets/nginx_key ${NGINX_DIRKEY}
EXPOSE	443
ENTRYPOINT ["nginx", "-g", "daemon off;"]
