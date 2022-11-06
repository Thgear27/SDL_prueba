all:
	g++ -std=c++17 ./src/main.cpp ./src/glad.cpp -I./include -o game.out -lSDL2

run:
	./game.out