#!/bin/bash
bison -d -v --graph parser.y
flex fileFlex.l
cc parser.tab.c lex.yy.c $(pkg-config --cflags --libs glib-2.0) -lfl 
./a.out
