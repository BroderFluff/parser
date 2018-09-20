parser: main.o lexer.o
	gcc -o parser main.o lexer.o -I.
