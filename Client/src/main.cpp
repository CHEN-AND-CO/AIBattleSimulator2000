#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
  Game game("127.0.0.1", 53013, "Alex");

  //auto v = game.getMap();

  auto b = game.getBuildings();

  return 0;
}
