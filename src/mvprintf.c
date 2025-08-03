#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include "x-tui.h"

static void back_to_start() {
	printf("\r");
}

static void move_cur(int x,int y) {
	printf("\e[%d;%dH", y, x);
}

void clear_screen() {
	printf("\e[H\e[J");
}

int get_terminal_size(int *x, int *y) {
	struct winsize ws;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) { // Get terminal size
		clear_screen();
		printf("We meet some errors: %s\n", strerror(errno));
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
	int ret = vprintf(fmt, args);
	va_end(args);
	return ret;
}
