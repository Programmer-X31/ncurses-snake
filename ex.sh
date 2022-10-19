echo "Compiling snake.c into objectfile..."
gcc -c src/snake.c -o bin/obj/snake.o
echo "Compiling main.c into objectfile..."
gcc -c src/main.c -o bin/obj/main.o
echo "Linking Objectfiles"
gcc -lncursesw -Wall -std=c99 -lm bin/obj/main.o bin/obj/snake.o -o bin/main


echo "Executing ..."
bin/main
