#syntax=docker/dockerfile:1
FROM alpine:3.19 AS mariadb
ARG	TOOL_CNF ADMN_USER WDPRSS_USER MDB_CNF_FL
ENV	ADMN_USER=${ADMN_USER} WDPRSS_USER=${WDPRSS_USER}
COPY ${TOOL_CNF} /tmp/configure.sh
COPY ${MDB_CNF_FL} /etc/my.cnf.d/my-mariadb-server.cnf
RUN	apk update
RUN	apk add mysql mysql-client openrc
RUN	--mount=type=secret,id=mariadb_admin_key,env=ADMN_KEY\
	--mount=type=secret,id=mariadb_wdprss_key,env=WDPRSS_KEY\
	. /tmp/configure.sh && ft_sql_to_mariadb
RUN	mariadb-install-db --user=mysql
EXPOSE 3306
ENTRYPOINT ["/usr/bin/mariadbd-safe"]
