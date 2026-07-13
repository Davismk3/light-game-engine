# Game Engine

A small C++17/OpenGL game engine with platform input, screen management, rendering passes, and a batched menu/button system.

## Requirements

- macOS with the command-line developer tools (`g++`/Apple Clang)
- GLFW (`brew install glfw`)
- GLAD and stb_image placed in this repository as follows:

```text
vendor/
  glad/include/glad/gl.h
  glad/src/gl.c
  stb/stb_image.h
```

## Build and run

Run these commands from the repository root:

```sh
g++ -std=c++17 \
  app/*.cpp \
  app/app_controls/*.cpp \
  app/app_screen/*.cpp \
  engine_v2/engine_core/*.cpp \
  engine_v2/engine_platform/*.cpp \
  engine_v2/engine_render/*.cpp \
  vendor/glad/src/gl.c \
  -Ivendor/glad/include \
  -Ivendor/stb \
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -lglfw \
  -framework Cocoa \
  -framework OpenGL \
  -framework IOKit \
  -o game

./game
```

Runtime asset paths are relative to the repository root, so launch the executable from there. Engine shaders are stored in `engine_v2/engine_assets/`.

## Screens and menus

Application screens inherit from `Screen` and implement `initialize`, `processInput`, `update`, `render`, and `shutdown`. Press `A` for the simulation screen and `S` for the title screen.

To create a menu, add buttons before initializing and drawing it:

```cpp
ButtonBounds bounds{0.0f, 0.0f, 0.4f, 0.15f};
ButtonStyle style{
    {0.5f, 0.5f, 0.5f},
    {0.6f, 0.7f, 0.6f},
    {0.5f, 1.0f, 0.5f},
    1.0f
};

m_menu.addButton(bounds, style);
m_menu.initialize();
```

Forward input with `m_menu.processInput(input)` and render with `m_menu.draw()`. The menu stores all button geometry in one mesh and draws each button from its indexed range so its visual state can use a different color.
