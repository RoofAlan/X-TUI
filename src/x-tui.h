#ifndef X_TUI_H_
#define X_TUI_H_

#include <stdarg.h>
#include "xgetch.h"

// Color definitions
#define COLOR_BLUE "\033[34m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_GREEN "\033[7;32m"
#define COLOR_RED "\033[31m"
#define COLOR_RESET "\033[0m"
#define COLOR_WHITE_UNDERLINE "\033[7m"

typedef void (*MenuFunc)(void);

typedef struct {
    int key;
    char *name; // Option name
    MenuFunc func;	// Option's function
} Option_t;

// Clean screen
void clear_screen();

// Create a menu
int x_menu(Option_t *options, const char *descript, const char *title, const char *color);

// Create Yes/No dialog
int x_yesno(const char *title, const char *color);

// Move cursor
int x_mvprintf(int x, int y, const char *fmt, ...);

#endif
