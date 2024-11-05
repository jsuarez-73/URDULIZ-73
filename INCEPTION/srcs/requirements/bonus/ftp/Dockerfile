#syntax=docker/dockerfile:1
FROM alpine:3.19 AS ftp
ARG	CONF_VSFTPD TOOL_VSFTPD
RUN	apk update
RUN	apk add vsftpd
COPY ${CONF_VSFTPD}/vsftpd.conf /etc/vsftpd/vsftpd.conf
COPY ${TOOL_VSFTPD}/init_ftp.sh /usr/local/bin/init_ftp.sh
RUN	adduser -D jsuarez- -h /opt -G root
RUN	--mount=type=secret,id=ftp_secret,env=PASS_FTP \
	. /usr/local/bin/init_ftp.sh && set_passwd_ftp_users
EXPOSE 21
ENTRYPOINT ["vsftpd"]
CMD ["/etc/vsftpd/vsftpd.conf"]
