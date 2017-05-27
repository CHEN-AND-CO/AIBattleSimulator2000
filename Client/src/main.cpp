#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
  std::string data;
  
  std::cout << "Nom : ";
  std::cin >> data;
  Game game("127.0.0.1", 53000, data);

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
