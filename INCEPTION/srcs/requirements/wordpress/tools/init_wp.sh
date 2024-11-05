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

function ft_set_bonus_config ()
{
	sed -i -e "/<?php.*/a \
	// adjust Redis host and port if necessary \\n\
	define( 'FS_METHOD', 'direct');\\n\
	define( 'WP_REDIS_HOST', 'redis' );\\n\
	define( 'WP_REDIS_PORT', 6379 );\\n\
	// change the prefix and database for each site to avoid cache data collisions\\n\
	define( 'WP_REDIS_PREFIX', 'jsuarez-.42.fr' );\\n\
	define( 'WP_REDIS_DATABASE', 0 ); // 0-15\\n\
	// reasonable connection and read+write timeouts\\n\
	define( 'WP_REDIS_TIMEOUT', 1 );\\n\
	define( 'WP_REDIS_READ_TIMEOUT', 1 );" /opt/wordpress/wp-config.php;
	chmod 777 /opt/wordpress/wp-content/
	echo -e "${MAGENTA}config file modified${RESET}";
}

function ft_init_wp ()
{
	cd /opt/wordpress
	wp core download;
	if [ ! -f /opt/wordpress/wp-config.php ] ;
	then
		wp config create --dbpass=WP_KEY;
	else
		echo -e "${MAGENTA}wp-config.php already exists${RESET}";
	fi
	wp core install --admin_password=ADMN_KEY;
	wp theme install poe --activate;
	if [ ${BONUS} == "1" ] ;
	then
		ft_set_bonus_config;
		wp plugin install redis-cache --activate;
		wp redis enable;
	fi
	exec php-fpm${VS} -F;
}

ft_init_wp;
