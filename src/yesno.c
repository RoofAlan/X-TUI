#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#include "x-tui.h"

// 定义颜色代码
#define COLOR_BLUE "\033[34m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_GREEN "\033[7;32m"
#define COLOR_RED "\033[31m"
#define COLOR_RESET "\033[0m"
#define COLOR_WHITE_UNDERLINE "\033[7m"

// 显示菜单（基于索引高亮）
static void show_yesno(int selected_index, const char *color, const char *title, Option_t *options) {
	int num_options = 0;
	while(options[num_options].name != NULL) {
		num_options++;
	}
	clear_screen();
	printf("\n");
	printf("		   %s\n", title);
	for (int i = 0; i < num_options; i++) {
		if (i == selected_index) {
			printf("		  %s> [%d] %s%s\n", color, options[i].key, options[i].name, COLOR_RESET);
		} else {
			printf("		  [%d] %s%s\n", options[i].key, options[i].name, COLOR_RESET);
		}
	}
}

// 读取单个字符
static int read_char() {
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

// 主菜单逻辑
int x_yesno(const char *title, const char *color) {
	Option_t options[] = {
		{1, "Yes", NULL},
		{0, "No", NULL},
		{0, NULL, NULL}
	};
	int selected_index = 0; // 使用数组索引而非key值
	int num_options = 0;
	while(options[num_options].name != NULL) num_options++;
	while (1) {
		show_yesno(selected_index, color, title, options);

		int ch = read_char();
		switch (ch) {
			case 'w':
			case 'W':
				// 上键：索引-1并循环
				selected_index = (selected_index - 1 + num_options) % num_options;
				break;
			case 's':
			case 'S':
				// 下键：索引+1并循环
				selected_index = (selected_index + 1) % num_options;
				break;
			case '\n':  // 回车键
				if (options[selected_index].key == 0) { // chose 'No'
					return 1;
				} else { // chose 'Yes'
					return 0;
				}
				return 1;
			default:
				break;
		}
	}
	return 0;
}
