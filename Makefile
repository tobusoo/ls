all: app

app: main.c
	gcc -Wall -Werror -o app main.c