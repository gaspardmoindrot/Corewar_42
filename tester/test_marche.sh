#!/bin/bash

program=../asm
map_valid=$1
map_good=0
map_total=0

echo "\033[0;33mBienvenue dans le checker - auteur : gmoindro & rbeaufre\033[0m\n"

mkdir 42 our
for rep in $*
do
	l=$((${#rep} - 2))
	map_valid=${rep:0:$l}
	map_total=$(($map_total + 1))
	b=$(42binaire/./asm $map_valid.s)
	if [ "$b" == "Writing output program to $map_valid.cor" ]; then
		mv $map_valid.cor 42
		a=$($program $map_valid.s)
		if [ "$a" != "Writing output program to $map_valid.cor" ]; then
			echo "\033[0;31m\t[KO] $map_valid.s\t\t#problem on your map_checker\033[0m"
		else
			mv $map_valid.cor our
			echo $map_valid > a
			x=`awk -F / '{print $NF}' a`
			rm a
			resultat=$(cmp 42/$x.cor our/$x.cor)
			if [ -z "$resultat" ]; then
				echo "\033[0;32m\t[OK] $map_valid.s \033[0m"
				map_good=$(($map_good + 1))
			else
				echo "\033[0;31m\t[KO] $map_valid.s\t\t#problem inside the .cor\033[0m"
			fi
		fi
	else
		a=$($program $map_valid.s)
		if [ "$a" != "Writing output program to $map_valid.cor" ]; then
			echo "\033[0;32m\t[OK] $map_valid.s \033[0m"
			map_good=$(($map_good + 1))
		else
			echo "\033[0;31m\t[KO] $map_valid.s      #you write the .cor even if it's a wrong map\033[0m"
			rm $map_valid.cor
		fi
	fi
done
rm -r 42 our
