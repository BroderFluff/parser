parser: main.o lexer.o token.o
	gcc -o parser main.o lexer.o token.o -I.

clean:
	rm *.o parser
