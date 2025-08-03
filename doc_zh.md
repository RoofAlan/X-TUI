# TUI 开发工具库说明

## 项目概览
- **发起人**: RoofAlan
- **发起日期**: 2025年1月27日
- **目的**: 简化终端图形化界面(TUI)开发，特别适合新手学习
- **核心优势**: 提供简单易用的API降低入门门槛

---

## 核心函数详解

### 1. 菜单显示函数 `x_menu()`
```c
x_menu(Option_t, BackGroundText, Title, Color);
```

#### 参数说明
| 参数 | 类型 | 说明 |
|------|------|------|
| `Option_t` | 结构体数组 | 菜单选项配置 |
| `BackGroundText` | 字符串 | 界面背景文本 |
| `Title` | 字符串 | 菜单标题 |
| `Color` | ANSI转义码 | 颜色控制符 |

#### 选项结构体格式
```c
typedef struct {
    int type;       // 选项类型
    char* text;     // 显示文本
    void (*func)(); // 关联函数指针
} Option_t;
```

#### 使用示例
```c
Option_t options = {
    {1, "功能选项1", NULL},
    {2, "功能选项2", NULL},
    {0, "退出程序", NULL}, 
    {0, NULL, NULL}  // 必须以此标记结束
};

while(1) {
    int result = x_menu(options, "TUI Demo v1.0", "主菜单", "\e[32;7m");
    if(result == 2) break; // 检测退出指令
}
```

#### 返回值说明
- `0`: 常规选项选择
- `2`: 用户选择退出项
- `-1`: 发生错误

---

### 2. 确认对话框 `x_yesno()`
```c
x_yesno(Title, Color);
```

#### 参数说明
| 参数 | 类型 | 说明 |
|------|------|------|
| `Title` | 字符串 | 对话框标题 |
| `Color` | ANSI转义码 | 颜色控制符 |

#### 使用示例
```c
int res = x_yesno("确认删除所有数据？", "\033[31;7m"); // 红底白字
if(res == 0) {
    delete_data();
} else {
    cancel_operation();
}
```

#### 返回值说明
- `0`: 用户选择"Yes"
- `1`: 用户选择"No"

---

### 3. 定位输出函数 `x_mvprintf()`
```c
x_mvprintf(X, Y, format, args...)
```

#### 参数说明
| 参数 | 类型 | 说明 |
|------|------|------|
| `X` | 整数 | 列位置 (从1开始) |
| `Y` | 整数 | 行位置 (从1开始) |
| `format` | 字符串 | 标准printf格式 |

#### 使用示例
```c
// 在第3行第10列显示红色警告
x_mvprintf(10, 3, "\033[31m警告: 磁盘空间不足!\033[0m\n"); 
```

---

### 4. 屏幕清空函数 `clear_screen()`
```c
clear_screen();
```

#### 使用说明
无参数调用，直接清除当前终端屏幕内容：
```c
clear_screen();  // 清屏并重置光标到(1,1)
```

---

## 使用建议
1. 所有函数均基于ANSI终端实现
2. 颜色参数使用标准ANSI转义序列
3. 菜单结构体必须以`{0, NULL, NULL}`结尾
4. 推荐使用RGB颜色宏定义保持代码可读性
