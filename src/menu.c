#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include "x-tui.h"

// Show menu
static void show_menu(int selected_index, const char *color, const char *descript, const char *title, Option_t *options) {
	int num_options = 0;
	while(options[num_options].name != NULL) {
		num_options++;
	}
	clear_screen();
	printf("%s\n", descript);

	int max_x = 0, max_y = 0;
	get_screen_size(&max_x, &max_y);
	size_t space_title = (max_x / 2) - strlen(title);

	for(size_t s_count = 0; s_count < space_title; s_count++) {
		printf(" ");
	}
	printf("%s\n", title);
	for (int i = 0; i < num_options; i++) {
		for(size_t s_count = 0; s_count < space_title; s_count++) {
			printf(" ");
		}
		if (i == selected_index) {
			printf("%s> [%d] %s%s\n", color, options[i].key, options[i].name, COLOR_RESET);
		} else {
			printf("[%d] %s%s\n", options[i].key, options[i].name, COLOR_RESET);
		}
	}
}

// Main menu
int x_menu(Option_t *options, const char *descript, const char *title, const char *color) {
	int selected_index = 0;
	int num_options = 0;
	while(options[num_options].name != NULL) num_options++;
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
			case '\n':  // Enter key
				if (options[selected_index].key == 0) { // 退出选项
					if(options[selected_index].func) {
						options[selected_index].func();
						return 2;
					} else {
						printf("\nExiting...\n");
						return 2;
					}
				}
				if (options[selected_index].func) {
					options[selected_index].func();
					return 0;
				} else {
					printf("\n[%s] 功能未实现\n", options[selected_index].name);
					sleep(1);
					return 0;
				}
				break;
			default:
				break;
		}
	}
	return 0;
}

// Yes no menu
int x_yesno(const char *title, const char *color) {
	Option_t options[] = {
		{1, "Yes", NULL},
		{2, "No", NULL},
		{0, NULL, NULL},
	};
	int selected_index = 0;
	int num_options = 0;
	while(options[num_options].name != NULL) num_options++;
	while (1) {
		show_menu(selected_index, color, "", title, options);

		int ch = xgetch();
		switch (ch) {
			case KEY_UP:
				selected_index = (selected_index - 1 + num_options) % num_options;
				break;
			case KEY_DOWN:
				selected_index = (selected_index + 1) % num_options;
				break;
			case '\n':  // Enter key
				if(options[selected_index].key == 1) {
					return 0;
				} else if (options[selected_index].key == 2) {
					return 1;
				} if (options[selected_index].key == 0) { // 退出选项
					if(options[selected_index].func) {
						options[selected_index].func();
						return 2;
					} else {
						printf("\nExiting...\n");
						return 2;
					}
				}
				if (options[selected_index].func) {
					options[selected_index].func();
					return 0;
				} else {
					printf("\n[%s] 功能未实现\n", options[selected_index].name);
					sleep(1);
					return 0;
				}
				break;
			default:
				break;
		}
	}
	return 0;
}
