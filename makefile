run: compile
	./a.out

compile:
	g++ -c main.cpp -std=c++11 -Wall -g
	g++ -c setup.cpp -std=c++11 -Wall -g
	g++ -c shader.cpp -std=c++11 -Wall -g
	g++ -c object.cpp -std=c++11 -Wall -g
	g++ -c GameObjects/paddle.cpp -std=c++11 -Wall -g
	g++ -c GameObjects/ball.cpp -std=c++11 -Wall -g
	g++ -c GameObjects/icon.cpp -std=c++11 -Wall -g
	g++ -c GameObjects/point.cpp -std=c++11 -Wall -g
	g++ main.o setup.o shader.o object.o paddle.o icon.o point.o ball.o -lGLEW -lglfw -lGL -std=c++11 -Wall -g
	rm main.o setup.o shader.o object.o paddle.o ball.o icon.o point.o
