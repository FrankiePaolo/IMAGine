#!/bin/bash
bison -d -v --graph parser.y
flex fileFlex.l
cc parser.tab.c lex.yy.c -lfl
./a.out
