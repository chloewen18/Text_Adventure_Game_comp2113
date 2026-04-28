CXX = g++
CXXFLAGS = -Wall -std=c++11

all: game

game: main.o file_system.o player.o action.o game_flow.o
	$(CXX) $(CXXFLAGS) -o game main.o file_system.o player.o action.o game_flow.o

main.o: main.cpp game_shared.h file_system.h game_flow.h player.h
	$(CXX) $(CXXFLAGS) -c main.cpp

file_system.o: file_system.cpp file_system.h game_shared.h
	$(CXX) $(CXXFLAGS) -c file_system.cpp

player.o: player.cpp player.h game_shared.h
	$(CXX) $(CXXFLAGS) -c player.cpp

action.o: action.cpp action.h game_shared.h
	$(CXX) $(CXXFLAGS) -c action.cpp

game_flow.o: game_flow.cpp game_flow.h game_shared.h player.h action.h
	$(CXX) $(CXXFLAGS) -c game_flow.cpp

clean:
	rm -f *.o game save.txt