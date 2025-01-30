#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "x-tui.h"

static void back_to_start() {
	printf("\r");
}

static void move_cur(int x,int y) {
	//printf("x: %d y: %d", x, y);
	/*for(int i=0; i<y; i++) {
		back_to_start();
		printf("\b");
	}
	for(int i=0; i<y; i++) {
		printf("\n");
	}
	for(int j=0; j<x; j++) {
		printf(" ");
	} */
	printf("\e[%d;%dH", y, x);
}

void clear_screen() {
	printf("\e[H\e[J");
}

int get_terminal_size(int *x, int *y) {
	struct winsize ws;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
		clear_screen();
		printf("We meet some errors...\n");
		return -1;
	}
	*x = ws.ws_col;
	*y = ws.ws_row;
	return 0;
}

int x_mvprintf(int x, int y, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	move_cur(x, y);
	vprintf(fmt, args);
	va_end(args);
}
