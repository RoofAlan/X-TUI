#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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

void input_test() {
	char input_buffer[256];
	int len = x_input(input_buffer, sizeof(input_buffer), "请输入您的姓名: ", "\033[32m");
	if (len > 0) {
		clear_screen();
		x_mvprintf(5, 7, "\033[32m您好, %s!\033[0m", input_buffer);
		x_mvprintf(5, 8, "\033[37m按任意键继续...\033[0m");
		xgetch();
	} else {
		clear_screen();
		x_mvprintf(5, 7, "\033[31m输入被取消或出错\033[0m");
		sleep(1);
	}
}

void progress_test() {
	clear_screen();
	int final_progress = x_progress(35, 50, "交互进度条", "\033[33m");
	clear_screen();
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
		snprintf(sc, sizeof(sc), "改变颜色(Now: %d)", ncolor);
		Option_t option[] = {
			{1, sc, set_color},
			{2, "输入测试", input_test},
			{3, "进度条测试", progress_test},
			{0, "返回", NULL},
			{0, NULL, NULL}
		};
		int res = x_menu(option, "X-TUI v1.3! - 设置菜单", "Settings", mcolor[ncolor]);
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
		int res = x_menu(option, "X-TUI v1.3! - 主题设置", "Themes", mcolor[ncolor]);
		if(res == 2) break;
	}
}

void yesno_test() {
	int res = x_yesno("确定要退出程序吗?", mcolor[ncolor]);
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
		{3, "输入测试", input_test},
		{4, "进度条测试", progress_test},
		{5, "系统设置", settings_action},
		{6, "主题", theme},
		{0, "退出程序", yesno_test},
		{0, NULL, NULL}
	};
	while(1) {
		x_menu(options, "X-TUI V1.3! - 增强版", "主菜单", mcolor[ncolor]);
	}
	return 0;
}
