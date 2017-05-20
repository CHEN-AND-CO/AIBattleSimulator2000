#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
  Game game("127.0.0.1", 53000, "Alex");

  while (getchar() != 'q') {
    game.getBuildings(sf::Color::Blue);
  }

  return 0;
}
