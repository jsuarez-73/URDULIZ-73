function ft_sql_to_mariadb ()
{
	cat >/tmp/${MDB_SQL} <<EOF
		CREATE USER '${WDPRSS_USER}'@'%' IDENTIFIED BY '${WDPRSS_KEY}';
		GRANT ALL ON wordpress.* TO '${WDPRSS_USER}'@'%' WITH GRANT OPTION;
		RENAME USER 'root'@'localhost' TO '${ADMN_USER}'@'localhost';
		SET PASSWORD FOR '${ADMN_USER}'@'localhost' = PASSWORD('${ADMN_KEY}');
		FLUSH PRIVILEGES;
EOF
}

function ft_conf_mariadb ()
{
	echo -e "[mariadb]\ndatadir=${DATADIR}\n" "init_file=/tmp/${MDB_SQL}\n"\
		"skip_networking=0\n" "bind_address=*"| cat >${DIR_MDB_CNF}/${MDB_CNF};
}
