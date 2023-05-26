# Jeu de la vie

Implementing game of life in C


## Deployment

To compile the project using clang on mac

```bash
  clang -v gui.c main.c board.c game.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf 
-lSDL2_mixer -lSDL2_image -o game_of_life
```
To compile the project using clang on Ubuntu

First we need to install the tools
```bash
sudo apt-get update
sudo apt-get install clang
sudo apt-get install git
sudo apt-get install libgbm1
sudo apt-get install libsdl2-*

```
Now we can compile the program

```bash
sudo clang -v gui.c main.c board.c game.c -I/usr/include/SDL2 -L/usr/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -o game_of_life
./game_of_life 25 40
```
25 for the number of lines and 40 for columns




## Authors

- [@ThomasHoutrique](https://github.com/ThomasHoutrique)

- [@lilnel16](https://github.com/lilnel16)
 To compile the project using on ubuntu