all:
	g++ -I src/include -L src/lib -o main C++/main.cpp -lmingw32 -lSDL3_test -lSDL3