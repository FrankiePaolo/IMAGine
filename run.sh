#!/bin/bash

if [ "$s" = "--compile" ] || [ "$2" = "-c" ]; then
	bison -d parser.y
	flex lexer.l
	gcc -o $1 *.c -lfl 
elif [ "$2"="--erase" ] || [ "$2"="-e" ]; then
	rm lex.yy.c parser.tab.* $1
else 
	rm lex.yy.c parser.tab.* $1
	bison -d parser.y
	flex lexer.l
	gcc -o $1 *.c -lfl
fi
