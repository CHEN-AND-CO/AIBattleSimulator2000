#include "Server.hpp"

Server::Server(const unsigned short port) {
  listner.listen(port);
  listner.setBlocking(false);
}

void Server::receivePackets(std::string& msg) {
  for (Clients::iterator it = clients.begin(); it != clients.end();) {
    sf::Packet packet;
    sf::Socket::Status status = it->second->receive(packet);

    switch (status) {
      case sf::Socket::Done:
        packet >> msg;
        std::cout << it->first << ": " << msg << "\n";
        ++it;
        break;

      case sf::Socket::Disconnected:
        std::cout << it->first << " has been disconnected\n";
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
    it->second->send(packet);
  }
}

void Server::send(const std::string& i, const std::string& msg) {
  sf::Packet packet;
  packet << msg;
  Clients::iterator tmp = clients.find(i);
  if (tmp == clients.end()) {
    std::cout << "No client found \n";
    return;
  }
  tmp->second->send(packet);
}

void Server::receive(std::string& msg) {
  sf::TcpSocket* nextClient = nullptr;

  if (nextClient == nullptr) {
    nextClient = new sf::TcpSocket;
    nextClient->setBlocking(false);
  }
  if (listner.accept(*nextClient) == sf::Socket::Done) {
    clients.insert(std::make_pair(std::to_string(clients.size()), nextClient));
    std::cout << clients.size()-1 << " is connected\n";
    nextClient = nullptr;
  }

  receivePackets(msg);
}
