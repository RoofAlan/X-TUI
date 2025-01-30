#ifndef X_TUI_H_
#define X_TUI_H_

#include <stdarg.h>

// 定义函数指针类型
typedef void (*MenuFunc)(void);

// 选项结构体
typedef struct {
    int key;
    char *name;
    MenuFunc func;
} Option_t;

void clear_screen();

int x_menu(Option_t *options, const char *descript, const char *title, const char *color);

int x_yesno(const char *title, const char *color);

int x_mvprintf(int x, int y, const char *fmt, ...);

#endif
