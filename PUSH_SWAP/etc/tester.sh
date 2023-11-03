#!/bin/bash

ROOT=~/Documents/Urduliz42/PUSH_SWAP
exec 4<$ROOT/etc/num_lists.txt;
exec 5<$ROOT/etc/error_lists.txt;
BLUE="1;34m";
GREEN="1;32m";
RED="1;31m";
WHITE="1;37m";
MAGENTA="1;35m";
PUSH_SWAP=$ROOT/push_swap;
if (ls $PUSH_SWAP | grep "push_swap")
then
	echo -e "\t\e[$MAGENTA Successfull Handlers Cases\e[0m";
	while read -u 4 -a BUFFER;
	do 
		echo -n -e "\e[$BLUE list length:\e[0m ${#BUFFER[@]} \t";
		lines=$($PUSH_SWAP ${BUFFER[@]} | wc -l);
		echo -n -e "\e[$MAGENTA Instructions length: $lines \e[0m \e[$BLUE\tResponse: \e[0m";
		response=$($PUSH_SWAP ${BUFFER[@]} | $ROOT/etc/checker_linux ${BUFFER[@]});
		if [[ $response = "OK" ]];
		then
			echo -e "\e[$GREEN OK\e[0m";
		elif [[ $response = "KO" ]];
		then
			echo -e "\e[$RED KO\e[0m";
		fi
	done
	echo -e "\t\e[$MAGENTA Error Handlers Cases\e[0m";
	while read -u 5 -a BUFFER_ERR;
	do
		echo -n -e "\e[$BLUE list length:\e[0m ${#BUFFER_ERR[@]} \t";
		response=$($PUSH_SWAP ${BUFFER_ERR[@]} 2>&1);
		exec 2>/dev/null;
		lines=$($PUSH_SWAP ${BUFFER_ERR[@]} | wc -l);
		if [[ $response = "Error" && $lines == 0 ]]
		then
			echo -e "\e[$GREEN Error\e[0m";
		elif [[ $response != "Error" && $lines > 1 ]]
		then
			echo -e "\e[$RED Not Error?\e[0m";
		fi
	done
else
	echo -e "\e[$RED Not executable push_swap file found.\e[0m";
fi
