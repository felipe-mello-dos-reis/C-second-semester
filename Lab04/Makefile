all:
	gcc -Wall -Werror -Wextra -pedantic -fsanitize=leak,address,undefined -g -O0 main.c btree.c queue.c -o main
run:
	./main