CFLAGS = -g -Wall -pedantic -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
#UNIT = -ftest-coverage -fprofile-arcs

SRC = $(wildcard src/*.cpp)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))

all: AIBattleSimulatorClient.out

remake: clean AIBattleSimulatorClient.out

AIBattleSimulatorClient.out : $(OBJ)
	g++ obj/* $(LDFLAGS) -o $@ $(OBJ)

obj/%.o: src/%.cpp
	g++ -c $< -Iinclude -o $@ $(CFLAGS)

clean:
	rm obj/*.o *.out *.gch -f

clear:
	rm obj/*.o *.gch -f
