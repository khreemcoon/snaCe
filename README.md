# snaCe
Snake game made in C and SDL2
##### *Only tested on linux*
# Dependencies
To compile and run this, you need SDL2 installed
(these commands install sdl2 and it's components as well as the development libraries)
To do that on ubuntu/debian-based distros, run these commands in your terminal:
`sudo apt-get install libsdl2-2.0-0 libsdl2-dev libsdl2-ttf-2.0-0 libsdl2-ttf-dev libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev`
Arch-based:
`sudo pacman -S sdl2 sdl2_image sdl2_mixer sdl2_ttf`
IF THESE COMMANDS DON'T WORK, PLEASE MAKE AN ISSUE.
# Compiling
To compile this(and launch it) just run
`gcc alltheotherslimshadysarejustimmitating.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o game && ./game`
## Modifying
You can also freely replace the textures(the .png's) and the sounds, as well as the font.
##### You can share this code as well as the images and sounds and all but do not advertise it as your own
