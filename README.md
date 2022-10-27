# C Snake Using Ncurses

Run the game by running the ex.sh file.
```sh
./ex.sh
```

Or run the Shell Code
```sh
mkdir -p bin/obj 2>> /dev/null

gcc -c -lncursesw src/snake.c -o bin/obj/snake.o
gcc -c -lncursesw src/main.c -o bin/obj/main.o
gcc -c -lncursesw src/food.c -o bin/obj/food.o
gcc -lncursesw -Wall -std=c99 -lm bin/obj/main.o bin/obj/snake.o bin/obj/food.o -o bin/snake-game

bin/snake-game
```

Sorry Windows Users... :)
