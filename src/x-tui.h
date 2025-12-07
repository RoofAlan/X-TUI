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

// Get screen size
int get_screen_size(int *x, int *y);

// Get user input as string (new function)
// Get user input as string (new function)
int x_input(char *buffer, int max_len, const char *prompt, const char *color);

// Hide/show cursor for smoother UI
void hide_cursor();
void show_cursor();

// Interactive moveable progress bar that responds to user input
int x_progress(int width, int add, const char *title, const char *color);

#endif
