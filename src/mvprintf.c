#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <limits.h>
#include <string.h>
#include "x-tui.h"

static void back_to_start() {
	printf("\r");
}

static void move_cur(int x, int y) {
	// Ensure coordinates are within valid range (1-based indexing)
	if (x < 1) x = 1;
	if (y < 1) y = 1;
	printf("\e[%d;%dH", y, x);
}

void clear_screen() {
	write(STDOUT_FILENO, "\e[H\e[2J\e[3J", 11);
	//fflush(stdout);
}

int get_screen_size(int *x, int *y) {
	if (!x || !y) {
		return -1;  // Invalid parameters
	}
	
	struct winsize ws;
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) { // Get terminal size
		return -1;
	}

	*x = ws.ws_col;
	*y = ws.ws_row;
	return 0;
}

int x_mvprintf(int x, int y, const char *fmt, ...) {
	if (!fmt) {
		return -1;  // Invalid format string
	}
	
	va_list args;
	va_start(args, fmt);
	move_cur(x, y);
	int ret = vprintf(fmt, args);
	fflush(stdout);  // Ensure output is flushed immediately
	va_end(args);
	return ret;
}

// Hide cursor
void hide_cursor() {
	printf("\e[?25l");
	fflush(stdout);
}

// Show cursor
void show_cursor() {
	printf("\e[?25h");
	fflush(stdout);
}


