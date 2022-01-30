all:
	gcc -Wall -Werror -Wextra -pedantic -fsanitize=leak,address,undefined -g -O0 main.c digraph.c stack.c -o main
run:
	gcc -Wall -Werror -Wextra -pedantic -fsanitize=leak,address,undefined -g -O0 main.c digraph.c stack.c -o main && ./main
