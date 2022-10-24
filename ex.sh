echo "Compiling snake.c into objectfile..."
gcc -c src/snake.c -o bin/obj/snake.o
echo "Compiling main.c into objectfile..."
gcc -c src/main.c -o bin/obj/main.o
echo "Compiling food.c into objectfile..."
gcc -c src/food.c -o bin/obj/food.o
echo "Linking Objectfiles"
gcc -lncursesw -Wall -std=c99 -lm bin/obj/main.o bin/obj/snake.o bin/obj/food.o -o bin/snake-game


echo "Executing ..."
bin/snake-game
