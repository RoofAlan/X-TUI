#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "x-tui.h"

// Interactive moveable progress bar that responds to user input
int x_progress(int width, int add, const char *title, const char *color) {
	if (width < 10) width = 10;  // Minimum width
	
	// Get screen size
	int screen_x = 0, screen_y = 0;
	get_screen_size(&screen_x, &screen_y);
	
	// Start at the center
	int pos_x = (screen_x - width) / 2;
	if (pos_x < 1) pos_x = 1;
	int pos_y = screen_y / 2;
	if (pos_y < 1) pos_y = 1;

	int progress = 0;
	int active = 1;  // Flag to continue the loop

	while (active) {
		// Clear screen and draw the progress bar at current position
		clear_screen();

		// Draw the outline box for progress bar
		// Top border
		for (int i = 0; i < width; i++) {
			x_mvprintf(pos_x + i, pos_y, "%s─%s", color, COLOR_RESET);
		}

		// Bottom border
		for (int i = 0; i < width; i++) {
			x_mvprintf(pos_x + i, pos_y + 2, "%s─%s", color, COLOR_RESET);
		}

		// Left and right borders
		x_mvprintf(pos_x - 1, pos_y + 1, "%s│%s", color, COLOR_RESET);
		x_mvprintf(pos_x + width, pos_y + 1, "%s│%s", color, COLOR_RESET);

		// Corners
		x_mvprintf(pos_x - 1, pos_y, "%s┌%s", color, COLOR_RESET);
		x_mvprintf(pos_x + width, pos_y, "%s┐%s", color, COLOR_RESET);
		x_mvprintf(pos_x - 1, pos_y + 2, "%s└%s", color, COLOR_RESET);
		x_mvprintf(pos_x + width, pos_y + 2, "%s┘%s", color, COLOR_RESET);

		// Draw title
		if (title) {
			int title_len = strlen(title);
			int title_pos = (width - title_len) / 2;
			if (title_pos < 0) title_pos = 0;
			x_mvprintf(pos_x + title_pos, pos_y, "%s%s%s", color, title, COLOR_RESET);
		}

		// Calculate the filled width of the progress bar
		int filled_width = (width * progress) / 100;
		if (filled_width > width - 2) filled_width = width - 2;  // Account for borders
		
		// Draw the progress bar inside the box
		for (int i = 0; i < filled_width; i++) {
			x_mvprintf(pos_x + i + 1, pos_y + 1, "%s█%s", color, COLOR_RESET);
		}
		
		// Fill the remaining space with empty progress indicator
		for (int i = filled_width; i < width - 2; i++) {
			x_mvprintf(pos_x + i + 1, pos_y + 1, "%s░%s", color, COLOR_RESET);
		}
		
		// Show percentage text in the middle of the progress bar
		char percent_str[10];
		snprintf(percent_str, sizeof(percent_str), "%d%%", progress);
		int percent_pos = (width - 2 - strlen(percent_str)) / 2;
		if (percent_pos < 0) percent_pos = 0;
		x_mvprintf(pos_x + percent_pos + 1, pos_y + 1, "%s%s%s", color, percent_str, COLOR_RESET);
		
		fflush(stdout);

		// Get user input
		int ch = xgetch();

		switch (ch) {
			case KEY_RIGHT:
				if (progress < 100) progress += add;
				if (progress > 100) progress = 100;
				break;
			case KEY_LEFT:
				if (progress > 0) progress -= add;
				if (progress < 0) progress = 0;
				break;
			case KEY_ESC:
			case '\n':
				active = 0;
				break;
			default:
				break;
		}
	}
	
	return progress;  // Return the final progress value
}
