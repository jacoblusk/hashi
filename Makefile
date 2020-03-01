main: main.o lexer.o token.o parser.o linkedlist.o
	gcc $^ -o $@ -fsanitize=address -fno-omit-frame-pointer

main.o: main.c lexer.h token.h parser.h types.h
	gcc -g -c $< -o $@

parser.o: parser.c token.h
	gcc -g -c $< -o $@

lexer.o: lexer.c token.h lexer.h
	gcc -g -c $< -o $@

token.o: token.c token.h
	gcc -g -c $< -o $@

linkedlist.o: linkedlist.c linkedlist.h
	gcc -g -c $< -o $@

clean:
	rm -f *.o main

.PHONY: clean