#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "src/x-tui.h"

const char *mcolor[] = {
	"\033[31;7m","\033[32;7m","\033[0;7m", "\033[33;7m"
};
int ncolor = 0;

// 示例功能函数
void option1_action() {
	printf("\n\033[32m执行Option1功能...\033[0m\n");
	sleep(1);
}

void option2_action() {
	x_mvprintf(10, 10, "\033[33m执行Option2功能...\033[0m\n");
	sleep(1);
}

void set_color() {
	if(ncolor < 3) {
		ncolor++;
	} else {
		ncolor=0;
	}
}

void settings_action() {
	while(1) {
		char sc[50];
		sprintf(sc, "改变颜色(Now: %d)",ncolor);
		Option_t option[] = {
			{1, sc, set_color},
			{0, "返回", NULL},
			{0, NULL, NULL}
		};
		int res = x_menu(option, "X-TUI v1.1!", "Settings", mcolor[ncolor]);
		if(res == 2) break;
	}
}

void theme() {
	Option_t option[] = {
		{1, "主题项一", NULL},
		{0, "返回", NULL},
		{0, NULL, NULL}
	};
	while(1) {
		int res = x_menu(option, "X-TUI V1.1!", "Themes", mcolor[ncolor]);
		if(res == 2) break;
	}
}

void yesno_test() {
	int res = x_yesno("Are you sure?", mcolor[ncolor]);
	if(res == 0) {
		exit(0);
	} else {
		return;
	}
}

int main(void) {
	clear_screen();
	// 选项数组（注意退出选项在最后位置）
	Option_t options[] = {
		{1, "功能一", option1_action},
		{2, "功能二", option2_action},
		{3, "系统设置", settings_action},
		{4, "主题", theme},
		{0, "退出程序", yesno_test},
		{0, NULL, NULL}
	};
	while(1) {
		x_menu(options, "X-TUI V1.1!", "MainMenu", mcolor[ncolor]);
	}
	return 0;
}
