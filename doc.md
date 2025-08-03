# TUI Development Toolkit Documentation

## Project Overview
- **Creator**: RoofAlan
- **Initiation Date**: January 27, 2025
- **Purpose**: Simplify Terminal User Interface (TUI) development with beginner-friendly APIs
- **Core Advantage**: Intuitive functions accelerate learning curve

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
    int type;       // Option identifier
    char* text;     // Display text
    void (*func)(); // Associated function 
} Option_t;
```

#### Usage Example
```c
Option_t options = {
    {1, "Data Processing", NULL},
    {2, "System Settings", NULL},
    {0, "Exit Program", NULL}, 
    {0, NULL, NULL}  // Mandatory termination marker
};

while(1) {
    int selection = x_menu(options, "TUI Framework v1.2", "Main Menu", "\e[34;1m");
    if(selection == 2) exit_safely();
}
```

#### Return Values
- `0`: Standard option selected
- `2`: Exit option chosen
- `-1`: Execution error

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
} else {
    cancel_operation();
}
```

#### Return Values
- `0`: "Yes" selected
- `1`: "No" selected

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

### 4. Screen Clear Function `clear_screen()`
```c
clear_screen();
```

#### Implementation Notes
Parameterless function that resets terminal display:
```c
clear_screen();  // Erases screen & positions cursor at (1,1)
```

---

## Development Guidelines
1. All functions utilize ANSI terminal standards
2. Color parameters require valid ANSI escape sequences
3. Menu arrays must terminate with `{0, NULL, NULL}`
4. Position coordinates use 1-based indexing system
