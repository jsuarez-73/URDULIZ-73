#syntax=docker/dockerfile:1
FROM alpine:3.19 AS mariadb
ARG	DATADIR MDB_CNF DIR_MDB_CNF TOOL_CNF ADMN_USER WDPRSS_USER MDB_SQL 
ENV	DATADIR=${DATADIR} MDB_CNF=${MDB_CNF} ADMN_USER=${ADMN_USER}\
	DIR_MDB_CNF=${DIR_MDB_CNF} WDPRSS_USER=${WDPRSS_USER} MDB_SQL=${MDB_SQL}
COPY ${TOOL_CNF} /tmp/configure.sh
RUN	apk update
RUN	apk add mysql mysql-client openrc vim
RUN	. /tmp/configure.sh && ft_conf_mariadb
RUN	--mount=type=secret,id=mariadb_admin_key,env=ADMN_KEY\
	--mount=type=secret,id=mariadb_wdprss_key,env=WDPRSS_KEY\
	. /tmp/configure.sh && ft_sql_to_mariadb
RUN	mariadb-install-db --user=mysql
EXPOSE 3306
ENTRYPOINT ["/usr/bin/mariadbd-safe"]

