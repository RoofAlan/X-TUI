# X-TUI

A simple Terminal UI frame for greenhorn

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

The compiled product is under src/, a static library called libx-tui.a

## Use

Just add "-L. -lx-tui" at compile time (make sure this library is in the current folder)

## Docs

See [doc.md](doc.md)
