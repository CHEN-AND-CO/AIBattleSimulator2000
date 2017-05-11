#include "Network.hpp"

Network::Network(int port) {
  selector.add(listener);

  if (listener.listen(53000) != sf::Socket::Done) {
    std::cerr << "Error listener\n";
    exit(-1);
  }
}

void Network::send(std::string message) {
  packet << message;
  client.send(packet);
}

void Network::receive() {
  if (selector.isReady(listener)) {
    if (listener.accept(client) == sf::Socket::Done) {
      std::cout << "New client" << std::endl;
      selector.add(client);
    }
  } else {
    if (selector.isReady(client)) {
      if (client.receive(packet) == sf::Socket::Done) {
      }
    }
  }
}