Flex_src = lexer.l
Bison_src = parser.y
OS_NAME := $(shell uname -s | tr A-Z a-z)

os:
	@echo $(OS_NAME)

parser.tab.c : $(Bison_src)
	bison -d $^

compiler-lex.c : $(Flex_src)
	flex $^;
	mv lex.yy.c $@

IMAGine : parser.tab.c compiler-lex.c *.c
	if [ ! -d ../bin ]; then mkdir ../bin; fi
	if [ "$(OS_NAME)" = "linux" ]; then gcc -g -lfl $^ -o IMAGine -lm -Wall `pkg-config vips --cflags --libs`; else gcc -g -ll $^ -o IMAGine -Wall `pkg-config vips --cflags --libs`; fi
	rm parser.tab.c ;
	rm compiler-lex.c ;
	rm parser.tab.h ;
	mv IMAGine ../bin/;

clean:
	rm ../bin/*.c;
	rm ../bin/*.h;
	rm ../bin/IMAGine;
