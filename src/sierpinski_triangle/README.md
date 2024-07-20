# Sierpinski Triangle

This is a simple program that generates a Sierpinski Triangle using SFML.

## How to run
### Option 1 - Default Dimensions
Compile: `cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release`

Build: `./build/bin/main`

### Option 2 - Custom Dimensions
Add a custom precision number. Default is 1 pixel. 

Compile: `cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release`

Build: `./build/bin/main <number>`