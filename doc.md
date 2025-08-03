***介绍***

    这是一个由RoofAlan在2025年1月27日发起的项目，目的在于更简单的实现终端图形化(TUI)，该项目更贴近新手学习

***基础函数***
 1. x_menu(): 这是最最最基础的函数之一，它能够显示一个菜单，使用方法如下:
格式：

```C
x_menu(Option_t, BackGroundText, Title, Color);
```

**使用示例**

```C
Option_t options = {
    {1, "Option 1", NULL}, // NULL可以改成void(*)()类的函数
    {2, "Option 2", NULL},
    {0, "Exit", NULL}, // 这里的NULL也行
    {0, NULL, NULL} // 这里必须是{0, NULL, NULL}
};
while(1) {
    int result = x_menu(options, "I'm background-text", "Title", "\e[32;7m"); // 颜色被定义为绿底黑字
    if(result == 2) break; // 退出
}
```

返回值说明：
0: 正常返回  2: 选中了退出
--

 2. x_yesno(): 显示一个菜单，用于让用户选择"Yes"或"No"
格式:

```C
x_yesno(Title, Color);
```

**使用示例**

```C
int res = x_yesno("Are you sure?", "\033[32;7m");
if(res == 0) {
    printf("You agreed\n");
} else {
    printf("You refused\n");
}
```

返回值说明:
0: 同意，即选中"Yes"  1: 拒绝，即选中"No"
--

 3. x_mvprintf(): 在屏幕的指定位置打印字符串
格式:

```C
x_mvprintf(X, Y, format, args...)
```

**使用示例**

```C
x_mvprintf(2, 5, "Hello %s", "world!\n"); // 在屏幕的第二列、第五行打印"Hello world!"和一个回车符(\n)
```

 4. clear_screen(): 清除屏幕，直接用就行
