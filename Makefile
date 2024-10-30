all: build
build:
	gcc *.cpp -o clicker -Wall -lSDL2 -lSDL2_ttf -g