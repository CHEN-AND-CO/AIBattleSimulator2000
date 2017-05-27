#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
  std::string data;
  std::cin >> data;
  Game game("172.17.3.250", 53000, data, sf::Color::Blue);

  while (getchar() != 'q') {
    auto map = game.getMap();
    for (auto& i : map) {
      for (auto& h : i) {
        std::cout << h;
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
