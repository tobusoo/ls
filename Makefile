all: app

app: src/main.c
	gcc -Wall -Werror -o app src/main.c