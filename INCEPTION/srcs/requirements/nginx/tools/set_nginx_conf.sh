#!/bin/sh
RESET="\033[0m"
RED_="\033[31m"
RED="\033[91m"
GREEN_="\033[32m"
GREEN="\033[92m"
function ft_set_nginx_conf ()
{
	echo -e "${GREEN}Setting configuration${RESET}";
	sed -i -e '/jpg/i \' -e '\tlocation ~ /adminer/ {\
		root	/var/www/;\
		proxy_pass	http://adminer:8080;\
		index	index.php;\
	}\n' /etc/nginx/conf.d/default.conf;
}

function run_conf_setup ()
{
	if [[ ${BONUS} == 1 ]];
	then
		echo -e "${GREEN}Bonus configuration started${RESET}";
		ft_set_nginx_conf;
	fi
}

run_conf_setup;
