#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
  Game game("127.0.0.1", 53000, "Alex", sf::Color::Blue);

  while (getchar() != 'q') {
    auto map = game.getMap(sf::Color::Blue);
    for (auto& i : map) {
      for (auto& h : i) {
        std::cout << h;
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
