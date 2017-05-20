CFLAGS = -g -Wall -pedantic -std=c++14
LDFLAGS = -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system
#UNIT = -ftest-coverage -fprofile-arcs

SRC = $(wildcard src/*.cpp)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))

all: AIBattleSimulatorServeur.out

remake: clean AIBattleSimulatorServeur.out

AIBattleSimulatorServeur.out : $(OBJ)
	g++ obj/* $(LDFLAGS) -o $@ 

obj/%.o: src/%.cpp
	g++ -c $< -Iinclude -o $@ $(CFLAGS) -fPIC

clean:
	rm obj/*.o *.out *.gch -f

clear:
	rm obj/*.o *.gch -f
