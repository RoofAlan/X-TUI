CC = gcc
AR = ar

all: libx-tui.a

libx-tui.a: menu.o yesno.o mvprintf.o
	$(AR) rcs libx-tui.a menu.o yesno.o mvprintf.o

menu.o: menu.c
	$(CC) menu.c -c -o menu.o
yesno.o: yesno.c
	$(CC) yesno.c -c -o yesno.o
mvprintf.o: mvprintf.c
	$(CC) mvprintf.c -c -o mvprintf.o

clean:
	rm -rf menu.o libx-tui.a yesno.o mvprintf.o
