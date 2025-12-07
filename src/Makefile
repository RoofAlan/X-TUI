CC = gcc
AR = ar

all: libx-tui.a

libx-tui.a: menu.o mvprintf.o getch.o input.o progress.o
	$(AR) rcs libx-tui.a menu.o mvprintf.o getch.o input.o progress.o

menu.o: menu.c
	$(CC) menu.c -c -o menu.o
mvprintf.o: mvprintf.c
	$(CC) mvprintf.c -c -o mvprintf.o
getch.o: getch.c
	$(CC) getch.c -c -o getch.o
input.o: input.c
	$(CC) input.c -c -o input.o
progress.o: progress.c
	$(CC) progress.c -c -o progress.o

clean:
	rm -rf menu.o libx-tui.a mvprintf.o getch.o input.o progress.o
