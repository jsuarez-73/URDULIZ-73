#!/bin/sh
RESET="\033[0m"
RED_="\033[31m"
RED="\033[91m"
GREEN_="\033[32m"
GREEN="\033[92m"
YELLOW="\033[93m"
BLUE_="\033[34m"
BLUE="\033[94m"
MAGENTA="\033[95m"
CYAN="\033[96m"
WHITE="\033[97m"

function ft_init_wp ()
{
	cd /opt/wordpress
	if [ ! -f /opt/wordpress/wp-config.php ] ;
	then
		wp config create --dbpass=WP_KEY;
	else
		echo -e "${MAGENTA}wp-config.php already exists${RESET}";
	fi
	wp core install --admin_password=ADMN_KEY;
	wp theme install poe --activate;
	exec php-fpm${VS} -F;
}

ft_init_wp;
