all:
	gcc -Wall -Werror -Wextra -pedantic -fsanitize=leak,address,undefined -g -O0 main.c expression.c -o main
run:
	gcc -Wall -Werror -Wextra -pedantic -fsanitize=leak,address,undefined -g -O0 main.c expression.c -o main && ./main
