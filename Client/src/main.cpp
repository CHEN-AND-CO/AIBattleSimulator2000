#include <SFML/Network.hpp>
#include <iostream>
#include "Client.hpp"

int main() {
  Client client("Allah");
  client.connect("127.0.0.1", 53000);

  std::string input = "", tmp = "";

  while (input.compare("/quit")) {
    input.clear();
    std::getline(std::cin, input);
    client.send(input);

    client.receive(tmp);
    if (tmp.length() > 0) {
      std::cout << "SERVER: " << tmp << std::endl;
      tmp.clear();
    }
  }
  return 0;
}
