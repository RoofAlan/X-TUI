# TUI Development Toolkit Documentation

## Project Overview
- **Creator**: RoofAlan
- **Initiation Date**: January 27, 2025
- **Purpose**: Simplify Terminal User Interface (TUI) development with beginner-friendly APIs
- **Core Advantage**: Intuitive functions accelerate learning curve
- **Latest Version**: v1.3 - Enhanced with input functions and improved safety

---

## Core Functions Reference

### 1. Menu Display Function `x_menu()`
```c
x_menu(Option_t, BackGroundText, Title, Color);
```

#### Parameter Specification
| Parameter | Type | Description |
|----------|------|-------------|
| `Option_t` | Struct array | Menu configuration structure |
| `BackGroundText` | String | Secondary UI text |
| `Title` | String | Primary menu title |
| `Color` | ANSI escape code | Text formatting sequence |

#### Option Structure Format
```c
typedef struct {
    int key;        // Option identifier
    char* name;     // Display text
    void (*func)(); // Associated function 
} Option_t;
```

#### Usage Example
```c
Option_t options[] = {
    {1, "Data Processing", data_processing_func},
    {2, "System Settings", system_settings_func},
    {0, "Exit Program", NULL}, 
    {0, NULL, NULL}  // Mandatory termination marker
};

while(1) {
    int selection = x_menu(options, "TUI Framework v1.3", "Main Menu", "\e[34;1m");
    if(selection == 2) break; // Exit selected
}
```

#### Return Values
- `0`: Standard option selected and executed
- `2`: Exit option chosen
- `-1`: Execution error or user cancelled (ESC key)

---

### 2. Confirmation Dialog `x_yesno()`
```c
x_yesno(Title, Color);
```

#### Parameter Specification
| Parameter | Type | Description |
|----------|------|-------------|
| `Title` | String | Prompt question |
| `Color` | ANSI escape code | Text formatting sequence |

#### Usage Example
```c
int response = x_yesno("Overwrite existing file?", "\033[33;1m"); // Yellow bold text
if(response == 0) {
    save_changes();
} else if (response == 1) {
    cancel_operation();
} else {
    // User cancelled with ESC
}
```

#### Return Values
- `0`: "Yes" selected
- `1`: "No" selected
- `-1`: User cancelled with ESC key

---

### 3. Positional Output `x_mvprintf()`
```c
x_mvprintf(X, Y, format, args...)
```

#### Parameter Specification
| Parameter | Type | Description |
|----------|------|-------------|
| `X` | Integer | Column position (1-based) |
| `Y` | Integer | Row position (1-based) |
| `format` | String | printf-compatible format |

#### Usage Example
```c
// Display warning at column 15, row 5
x_mvprintf(15, 5, "\033[31mALERT: System overload!\033[0m\n"); 
```

---

### 4. Text Input Function `x_input()` (NEW)
```c
x_input(buffer, max_len, prompt, color);
```

#### Parameter Specification
| Parameter | Type | Description |
|----------|------|-------------|
| `buffer` | char* | Buffer to store input |
| `max_len` | Integer | Maximum buffer length |
| `prompt` | String | Prompt text |
| `color` | String | Color formatting sequence |

#### Usage Example
```c
char name[256];
int len = x_input(name, sizeof(name), "Enter your name: ", "\033[32m");
if (len > 0) {
    printf("Hello, %s!\n", name);
}
```

#### Return Values
- `>0`: Length of input string
- `-1`: Error or user cancelled (ESC key)

#### Notes
- The dialog automatically centers on the screen and clears the screen before showing
- No position parameters needed - always appears in the center of the screen

### 5. Progress Bar Function `x_progress()` (NEW)
```c
x_progress(width, progress, title, color);
```

#### Parameter Specification
| Parameter | Type | Description |
|----------|------|-------------|
| `width` | Integer | Width of the progress bar |
| `progress` | Integer | Progress percentage (0-100) |
| `title` | String | Title to display on the progress bar |
| `color` | String | Color formatting sequence |

#### Usage Example
```c
// Show centered progress bar with width 30, 50% progress
x_progress(30, 50, "Loading...", "\033[32m");

// Update progress to 75%
x_progress(30, 75, "Loading...", "\033[32m");
```

#### Notes
- Creates an outlined box with a progress bar inside
- The progress bar is always centered on the screen
- The progress percentage is displayed in the center of the bar
- Progress is visualized with filled blocks (█) and empty blocks (░)

### 6. Interactive Moveable Progress Bar Function `x_progress_interactive()` (NEW)
```c
x_progress_interactive(width, title, color);
```

#### Parameter Specification
| Parameter | Type | Description |
|----------|------|-------------|
| `width` | Integer | Width of the progress bar |
| `title` | String | Title to display on the progress bar |
| `color` | String | Color formatting sequence |

#### Usage Example
```c
// Show interactive progress bar that user can move and adjust
int final_progress = x_progress_interactive(30, "Moveable Progress", "\033[32m");
printf("Final progress: %d%%\n", final_progress);
```

#### Controls
- **Arrow Keys**: Move the progress bar around the screen
- **+/- Keys**: Increase/decrease progress value
- **ESC Key**: Exit the interactive mode

#### Return Values
- `0-100`: Final progress percentage when user exits

#### Notes
- Creates an outlined box with a progress bar that can be moved by user
- Shows current position and progress percentage
- User has full control over position and progress value

---

### 5. Screen Clear Function `clear_screen()`
```c
clear_screen();
```

#### Implementation Notes
Parameterless function that resets terminal display:
```c
clear_screen();  // Erases screen & positions cursor at (1,1)
```

### 6. Screen Size Function `get_screen_size()`
```c
get_screen_size(int *x, int *y);
```

#### Parameter Specification
| Parameter | Type | Description |
|----------|------|-------------|
| `x` | int* | Pointer to store number of columns |
| `y` | int* | Pointer to store number of rows |

#### Return Values
- `0`: Success
- `-1`: Error getting screen size

---

## Development Guidelines
1. All functions utilize ANSI terminal standards
2. Color parameters require valid ANSI escape sequences
3. Menu arrays must terminate with `{0, NULL, NULL}`
4. Position coordinates use 1-based indexing system
5. Always check return values for error handling
6. Use `snprintf` instead of `sprintf` to prevent buffer overflows
7. User can cancel most operations with ESC key
