#include <SFML/Network.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
  // Client client("Kevin");
  // client.connect("127.0.0.1", 53000);

  // std::string input = "", tmp = "";

  // while (input.compare("/quit")) {
  //   input.clear();
  //   std::getline(std::cin, input);
  //   client.send(input);

  //   tmp = client.receive();
  //   if (tmp.length() > 0) {
  //     std::cout << "Serveur: " << tmp << std::endl;
  //     tmp.clear();
  //   }
  // }
  Game game("127.0.0.1", 53013, "Kevin");

  auto v = game.getMap();
  for (auto& i : v) {
    for (auto& j : i) {
      std::cout << j;
    }
    std::cout << std::endl;
  }

  return 0;
}
