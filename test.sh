#!/bin/bash

if [ $# -ne 1 ]
then
	echo 'error: use > test.sh n, n is the number of client you want'
else
	echo $i
	let i=1
	while [ $i -le $1 ]
	do
		pseudo=pseudo$1
		xterm -e irssi -c 127.0.0.1 -p 6667 -n pseudo &
		echo 'lancement de xterm'
		let i=$i+1
	done
fi
