# X-TUI

一个简单的终端UI框架，适合给新手学习

## Before build

***Archlinux
```bash
sudo pacman -S binutils gcc
```
***Debian & Ubuntu
```bash
sudo apt install binutils gcc
```

## Build

```bash
# Clone this repo
cd X-TUI && make
```

编译后的产物在src/下，一个名为libx-tui.a的静态库

## Use

只需要在编译时加入"-L. -lx-tui"即可（确保这个库在当前文件夹下）

## Docs

参考[doc.md](doc.md)
