exe:	main.cpp
	g++ *.cpp src/*.cpp src/*.c `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -o Othello

run:
	./Othello

r:
	./Othello

clean:
	rm Othello

c:
	rm Othello
