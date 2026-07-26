Architecture:

engine_v2/
├── engine_config.hpp                         -> ([hpp](../engine_config.hpp))
├── engine_docs/
│   ├── ENGINE.md                             -> ([md](ENGINE.md))
│   └── ENGINE_ARCHITECTURE.md                -> ([md](ENGINE_ARCHITECTURE.md))
.
# ASSETS: ====================================================================== #
Shared rendering assets are stored here.
The basic shaders transform and shade engine geometry.
The font atlas supplies glyph textures for menu text.
.
├── engine_assets/
│   ├── basic.vert                              -> ([vert](../engine_assets/basic.vert))
│   ├── basic.frag                              -> ([frag](../engine_assets/basic.frag))
│   └── font.png                                -> ([png](../engine_assets/font.png))
.
# PLATFORM: ==================================================================== #
Platform-facing window, input, and button interaction systems are stored here.
Defines [Window], which owns the application window and OpenGL context.
Defines [Input], which tracks keyboard and mouse state transitions.
Defines [TextBox], which handles user typing on-screen text in designated text boxes.
Defines [Button], which handles bounds, hover, and press states.
.
├── engine_platform/
│   ├── window.(hpp/cpp)                        -> ([hpp](../engine_platform/window.hpp))
│   ├── input.(hpp/cpp)                         -> ([hpp](../engine_platform/input.hpp))
│   ├── textbox.(hpp/cpp)                       -> ([hpp](../engine_platform/textbox.hpp))
│   └── button.(hpp/cpp)                        -> ([hpp](../engine_platform/button.hpp))
.
# RENDER: ====================================================================== #
General graphics resources and rendering commands are stored here.
Defines [GraphicsContext], which configures frame and render-pass state.
Defines [Camera], [Primitive], [Mesh], [Shader], and [Texture].
Defines [Menu] and [Text] for rendering interface elements.
.
├── engine_render/
│   ├── context.(hpp/cpp)                       -> ([hpp](../engine_render/context.hpp))
│   ├── camera.(hpp/cpp)                        -> ([hpp](../engine_render/camera.hpp))
│   ├── primitive.(hpp/cpp)                     -> ([hpp](../engine_render/primitive.hpp))
│   ├── mesh.(hpp/cpp)                          -> ([hpp](../engine_render/mesh.hpp))
│   ├── shader.(hpp/cpp)                        -> ([hpp](../engine_render/shader.hpp))
│   ├── texture.(hpp/cpp)                       -> ([hpp](../engine_render/texture.hpp))
│   ├── draw.(hpp/cpp)                          -> ([hpp](../engine_render/draw.hpp))
│   ├── menu.(hpp/cpp)                          -> ([hpp](../engine_render/menu.hpp))
│   └── text.(hpp/cpp)                          -> ([hpp](../engine_render/text.hpp))
.
# UTILITY: ===================================================================== #
Reusable mathematics, geometry, random generation, and timing helpers are stored here.
Defines vector, matrix, and quaternion types used throughout the engine.
Provides geometric queries, procedural noise, and frame timing.
.
└── engine_utility/
    ├── math.hpp                                -> ([hpp](../engine_utility/math.hpp))
    ├── vector.hpp                              -> ([hpp](../engine_utility/vector.hpp))
    ├── matrix.hpp                              -> ([hpp](../engine_utility/matrix.hpp))
    ├── quaternion.(hpp/cpp)                    -> ([hpp](../engine_utility/quaternion.hpp))
    ├── geometry.(hpp/cpp)                      -> ([hpp](../engine_utility/geometry.hpp))
    ├── random.(hpp/cpp)                        -> ([hpp](../engine_utility/random.hpp))
    └── time.(hpp/cpp)                          -> ([hpp](../engine_utility/time.hpp))
