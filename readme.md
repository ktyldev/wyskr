#   wyskr

Lightweight C++/OpenGL/SDL engine mostly for personal education purposes. Ultimate goal of supporting virtual reality development on relatively low-end hardware.

## todo

listed in approximate order of priority

*   bug: fix transform parenting - why is it upside down
*   bug: laggy after a longer run - defocusing window seems to be important?

*   refactor input into axes

*   directional light component
*   support multiple directional lights
*   point lights
*   spot lights

*   organise include files
*   automatic versioning
*   more primitives
*   load arbitrary meshes
*   find some way to optimise shader usage - it's possible for shaders to be compiled multiple times as part of different materials
*   make main loop framerate independent, currently relying on sdl's frame cap
*   use cmake to handle cross-platform development

*   handle fullscreen window
*   check for dependencies on startup

