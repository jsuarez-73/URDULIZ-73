#!/bin/sh
#
function ft_init_mariadb ()
{
	mariadb < /tmp/${MDB_SQL};
}

ft_init_mariadb;
