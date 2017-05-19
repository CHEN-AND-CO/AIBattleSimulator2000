#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
  Game game("172.17.3.250", 53000, "Alex");

  // auto v = game.getMap();

  // auto b = game.getBuildings();
  while(getchar()!='q'){}

  return 0;
}
