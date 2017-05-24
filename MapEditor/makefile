CFLAGS = -g -Wall -pedantic -std=c++14
LDFLAGS = -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system
#UNIT = -ftest-coverage -fprofile-arcs

SRC = $(wildcard *.cpp)
NOM = $(basename $(notdir $(SRC)))
OBJ = $(addsuffix .o, $(NOM))

all: MapEditor.out

remake: clean MapEditor.out

MapEditor.out : $(OBJ)
	g++ *.o $(LDFLAGS) -o $@ 

%.o: %.cpp
	g++ -c $< -o $@ $(CFLAGS)

clean:
	rm *.o *.out *.gch -f

clear:
	rm *.o *.gch -f
