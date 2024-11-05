#!/bin/sh

function set_passwd_ftp_users ()
{
	echo -e "${PASS_FTP}\n${PASS_FTP}" | passwd jsuarez-;
}
