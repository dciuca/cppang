# cppang 🎮

A game loosely inspired by the classic **Super Pang**, built as a learning project to explore C++ in a game development context. This is my first C++ game — the goal was to get hands-on experience with the language, game loops, physics, and state management using raylib as the rendering layer.

I welcome any kind of feedback: code corrections, refactoring suggestions, performance improvements — anything that helps me grow. Feel free to contribute new levels by editing `GameLevels.h`!

![cppang](assets/cppang.gif)

## Built with

- C++17
- [raylib 6.0](https://github.com/raysan5/raylib) — statically linked, vendored for both Linux and Windows (no installation required)

## Build

```bash
cmake -B build
cmake --build build
```

No dependencies to install on Windows. On Linux, the X11 and OpenGL system libraries are required:

```bash
sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl-dev
```

## WSL workaround (after Ubuntu upgrade)

If the window stops rendering after a WSL/Ubuntu upgrade, run this from an admin PowerShell:

```powershell
wsl --system sh -lc "pkill -9 weston"
```
