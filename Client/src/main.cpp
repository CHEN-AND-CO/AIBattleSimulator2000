#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
<<<<<<< HEAD
  Game game("127.0.0.1", 53000, "Alex", sf::Color::Blue);

  while (getchar() != 'q') {
    auto map = game.getMap(sf::Color::Blue);
=======
  std::string data;
  std::cin >> data;
  Game game("172.17.3.250", 53000, data);

  while (getchar() != 'q') {
    auto map = game.getMap();
>>>>>>> advancedServerImplement
    for (auto& i : map) {
      for (auto& h : i) {
        std::cout << h;
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
