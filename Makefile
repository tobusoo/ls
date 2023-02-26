all: app

app: src/main.o src/ls.o src/arguments.o
	gcc -Wall -Werror -o app src/main.o src/ls.o src/arguments.o

src/main.o: src/main.c
	gcc -Wall -Werror -c -o src/main.o src/main.c

src/ls.o: src/ls.c
	gcc -Wall -Werror -c -o src/ls.o src/ls.c

src/arguments.o: src/arguments.c
	gcc -Wall -Werror -c -o src/arguments.o src/arguments.c

clean:
	rm app src/main.o src/ls.o

run:
	./app