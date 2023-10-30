#!/bin/bash

exec 4<list.txt;
BLUE="1;34m";
GREEN="1;32m";
RED="1;31m";
WHITE="1;37m";
MAGENTA="1;35m";
while read -u 4 -a BUFFER;
do 
	echo -n -e "\e[$BLUE list length:\e[0m ${#BUFFER[@]} \t";
	lines=$(../push_swap ${BUFFER[@]} | wc -l);
	echo -n -e "\e[$MAGENTA Instructions length: $lines \e[0m \e[$BLUE\tResponse: \e[0m";
	response=$(../push_swap ${BUFFER[@]} | ./checker_linux ${BUFFER[@]});
	if (($response == "OK"))
	then
		echo -e "\e[$GREEN OK\e[0m"
	elif (($response == "KO"))
	then
		echo -e "\e[$RED KO\e[0m"
	fi
done
