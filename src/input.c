#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "x-tui.h"

// Get user input as string
int x_input(char *buffer, int max_len, const char *prompt, const char *color) {
	if (!buffer || max_len <= 0 || !prompt || !color) {
		return -1;  // Invalid parameters
	}

	if (max_len < 2) {
		return -1;  // Need at least 2 chars for null terminator
	}

	// Clear screen before showing the input dialog
	clear_screen();

	// Get screen size to center the input dialog
	int screen_x = 0, screen_y = 0;
	get_screen_size(&screen_x, &screen_y);

	// Calculate center position for the dialog
	int prompt_len = strlen(prompt);
	int center_x = (screen_x - prompt_len) / 2;
	if (center_x < 1) center_x = 1;
	int center_y = screen_y / 2;
	if (center_y < 1) center_y = 1;

	// Display the prompt in the center
	x_mvprintf(center_x, center_y, "%s%s", color, prompt);

	int pos = center_x + prompt_len;  // Position cursor after the prompt
	int input_pos = 0;
	char ch;

	while (1) {
		// Use internal move_cur function to position cursor
		printf("\e[%d;%dH", center_y, pos + input_pos);
		fflush(stdout);

		ch = xgetch();

		if (ch == KEY_ENTER || ch == '\n' || ch == '\r') {
			buffer[input_pos] = '\0';  // Null terminate
			break;
		} else if (ch == KEY_BKSPE || ch == 127 || ch == '\b') {  // Backspace
			if (input_pos > 0) {
				input_pos--;
				// Clear the character visually
				printf("\e[%d;%dH", center_y, pos + input_pos);
				printf(" ");
				printf("\e[%d;%dH", center_y, pos + input_pos);
				fflush(stdout);
			}
		} else if (ch == KEY_ESC) {
			return -1;  // Cancelled by user
		} else if (ch >= 32 && ch <= 126) {  // Printable ASCII characters
			if (input_pos < max_len - 1) {  // Leave space for null terminator
				buffer[input_pos] = ch;
				input_pos++;
				// Print the character
				printf("\e[%d;%dH", center_y, pos + input_pos - 1);
				printf("%c", ch);
				fflush(stdout);
			}
		}
		// Ignore other control characters
	}

	// Move cursor to next line after input
	printf("\e[%d;%dH", center_y + 1, 1);
	fflush(stdout);

	return input_pos;  // Return the length of the input string
}
