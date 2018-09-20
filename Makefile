parser: main.o lexer.o token.o cmd_parse.o
	gcc -o parser main.o lexer.o token.o cmd_parse.o -I. -Wall -O2

clean:
	rm *.o parser
