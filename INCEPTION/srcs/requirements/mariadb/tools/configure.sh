function ft_sql_to_mariadb ()
{
	cat >/tmp/set_mariadb.sql <<EOF
		CREATE USER '${WDPRSS_USER}'@'%' IDENTIFIED BY '${WDPRSS_KEY}';
		CREATE DATABASE wordpress;
		GRANT ALL ON wordpress.* TO '${WDPRSS_USER}'@'%' WITH GRANT OPTION;
		RENAME USER 'root'@'localhost' TO '${ADMN_USER}'@'localhost';
		SET PASSWORD FOR '${ADMN_USER}'@'localhost' = PASSWORD('${ADMN_KEY}');
		FLUSH PRIVILEGES;
EOF
}
