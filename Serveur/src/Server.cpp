#include "Server.hpp"

Server::Server(unsigned short port) {
  listner.listen(port);
  listner.setBlocking(false);
}

void Server::receivePackets() {
  std::string msg;
  for (Clients::iterator it = clients.begin(); it != clients.end();) {
    sf::Packet packet;
    sf::Socket::Status status = it->first->receive(packet);

    switch (status) {
      case sf::Socket::Done:
        packet >> msg;
        std::cout << it->second << ": " << msg << "\n";
        ++it;
        break;

      case sf::Socket::Disconnected:
        std::cout << it->second << " has been disconnected\n";
        it = clients.erase(it);
        break;

      default:
        ++it;
      break;
    }
  }
}

void Server::broadCast(const std::string& msg) {
  for (Clients::iterator it = clients.begin(); it != clients.end(); ++it) {
    sf::Packet packet;
    packet << msg;
    it->first->send(packet);
  }
}

void Server::receive() {
  sf::TcpSocket* nextClient = nullptr;

  if (nextClient == nullptr) {
    nextClient = new sf::TcpSocket;
    nextClient->setBlocking(false);
  }
  if (listner.accept(*nextClient) == sf::Socket::Done) {
    clients.insert(std::make_pair(nextClient, std::to_string(clients.size())));
    nextClient = nullptr;
  }

  receivePackets();
}
