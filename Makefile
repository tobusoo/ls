all: app

app: src/main.o src/ls.o
	gcc -Wall -Werror -o app src/main.o src/ls.o

src/main.o: src/main.c
	gcc -Wall -Werror -c -o src/main.o src/main.c

src/ls.o: src/ls.c
	gcc -Wall -Werror -c -o src/ls.o src/ls.c

clean:
	rm app src/main.o src/ls.o

run:
	./app