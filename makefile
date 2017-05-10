CFLAGS = -g -Wall -pedantic -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
#UNIT = -ftest-coverage -fprofile-arcs

SRC = $(wildcard src/*.cpp)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addprefix obj/, $(addsuffix .o, $(NOM)))

all: simu.out

remake: clean simu.out

simu.out : $(OBJ)
	g++ obj/* $(LDFLAGS) -o $@ $(OBJmake)

obj/%.o: src/%.cpp
	g++ -c $< -Iinclude -o $@ $(CFLAGS)

clean:
	rm obj/*.o *.out *.gch -f

clear:
	rm obj/*.o *.gch -f
