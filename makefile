compile:./main.cpp
	g++ -c ./main.cpp ./util.cpp ./snake.cpp ./snakeGame.cpp -g
	g++ main.o snake.o snakeGame.o util.o -o app -lsfml-graphics -lsfml-window -lsfml-system -g

run:
	./app