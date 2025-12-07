#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include "x-tui.h"

// Show menu
static void show_menu(int selected_index, const char *color, const char *descript, const char *title, Option_t *options) {
	if (!options || !color || !descript || !title) {
		return;  // Invalid parameters
	}
	
	int num_options = 0;
	// Count options but limit to prevent infinite loops
	while(options[num_options].name != NULL && num_options < 1000) {
		// Validate that each option has valid content
		if (options[num_options].name == NULL) {
			break;
		}
		num_options++;
	}
	
	if (num_options <= 0) {
		return;  // No options to display
	}
	
	clear_screen();
	printf("%s\n", descript);

	// Print for title
	int max_x = 0, max_y = 0;
	int space_title;
	if (get_screen_size(&max_x, &max_y) == 0 && title != NULL) {  // Only center if we got screen size
		size_t title_len = strlen(title);
		space_title = (title_len <= (size_t)max_x) ? (max_x / 2) - title_len/2 : 0;
		if (space_title < 0) space_title = 0;

		for(int s_count = 0; s_count < space_title; s_count++) {
			printf(" ");
		}
	}
	printf("%s\n", title);
	
	for (int i = 0; i < num_options; i++) {
		// Validate option before displaying
		if (options[i].name == NULL) {
			continue;  // Skip invalid options
		}

		if (get_screen_size(&max_x, &max_y) == 0 && title != NULL) {  // Re-center each option line
			if (space_title < 0) space_title = 0;

			for(int s_count = 0; s_count < space_title; s_count++) {
				printf(" ");
			}
		}

		if (i == selected_index) {
			printf("%s> [%d] %s%s\n", color, options[i].key, options[i].name, COLOR_RESET);
		} else {
			printf("[%d] %s%s\n", options[i].key, options[i].name, COLOR_RESET);
		}
	}
	fflush(stdout);  // Ensure output is flushed immediately
}

// Main menu
int x_menu(Option_t *options, const char *descript, const char *title, const char *color) {
	if (!options || !descript || !title || !color) {
		return -1;  // Invalid parameters
	}
	
	int selected_index = 0;
	int num_options = 0;
	// Count options but limit to prevent infinite loops
	while(options[num_options].name != NULL && num_options < 1000) num_options++;
	
	if (num_options <= 0) {
		return -1;  // No valid options
	}
	
	while (1) {
		show_menu(selected_index, color, descript, title, options);

		int ch = xgetch();
		switch (ch) {
			case KEY_UP:
				selected_index = (selected_index - 1 + num_options) % num_options;
				break;
			case KEY_DOWN:
				selected_index = (selected_index + 1) % num_options;
				break;
			case '\n':  // Enter key (which is the same as KEY_ENTER = 10)
				if (options[selected_index].key == 0) {
					if(options[selected_index].func) {
						options[selected_index].func();
						return 2;
					} else {
						printf("\nExiting...\n");
						fflush(stdout);
						return 2;
					}
				}
				if (options[selected_index].func) {
					options[selected_index].func();
					return 0;
				} else {
					return 0;
				}
				break;
			case KEY_ESC:  // Add escape key support
				return -1;
			default:
				break;
		}
	}
	return 0;
}

// Yes no menu
int x_yesno(const char *title, const char *color) {
	if (!title || !color) {
		return -1;  // Invalid parameters
	}
	
	Option_t options[] = {
		{1, "Yes", NULL},
		{2, "No", NULL},
		{0, NULL, NULL},
	};
	int selected_index = 0;
	int num_options = 2;  // We know there are 2 options before the terminator
	
	while (1) {
		show_menu(selected_index, color, "", title, options);

		int ch = xgetch();
		switch (ch) {
			case KEY_UP:
			case 'y':
			case 'Y':
				selected_index = 0;  // Select "Yes"
				break;
			case KEY_DOWN:
			case 'n':
			case 'N':
				selected_index = 1;  // Select "No"
				break;
			case '\n':  // Enter key (which is the same as KEY_ENTER = 10)
				if(options[selected_index].key == 1) {
					return 0;
				} else if (options[selected_index].key == 2) {
					return 1;
				}
				break;
			case KEY_ESC:  // Add escape key support
				return -1;
			default:
				break;
		}
	}
	return 0;
}
