
Build With:

g++ -std=c++17 \
  app/*.cpp \
  app/app_controls/*.cpp \
  app/app_screen/*.cpp \
  engine_v2/engine_core/*.cpp \
  engine_v2/engine_platform/*.cpp \
  engine_v2/engine_render/*.cpp \
  "../Voxel Engine/vendor/glad/src/gl.c" \
  -I"../Voxel Engine/vendor/glad/include" \
  -I"../Voxel Engine/vendor/stb" \
  -I/opt/homebrew/include \
  -L/opt/homebrew/lib \
  -lglfw \
  -framework Cocoa \
  -framework OpenGL \
  -framework IOKit \
  -o game

Run With: 

./game