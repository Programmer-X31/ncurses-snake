# C Snake Using Ncurses

Run the game by running the ex.sh file.
```sh
./ex.sh
```
Or
```sh
mkdir -p bin/obj 2>> /dev/null

gcc -c -lncursesw src/snake.c -o bin/obj/snake.o
gcc -c -lncursesw src/main.c -o bin/obj/main.o
gcc -c -lncursesw src/food.c -o bin/obj/food.o
gcc -lncursesw -Wall -std=c99 -lm bin/obj/main.o bin/obj/snake.o bin/obj/food.o -o bin/snake-game

bin/snake-game
```


As for the controls, use the WASD keys to move, and press X whenerver you want to exit the game. The Food is green in color, and the snake is white.

Sorry Windows Users... :)
