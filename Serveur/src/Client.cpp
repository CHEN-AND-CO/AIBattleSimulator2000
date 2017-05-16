#include "Client.hpp"

Client::Client(const std::string cname) { name = cname; }

sf::Socket::Status Client::connect(const sf::IpAddress& IP,
                                   unsigned short port) {
  // connect to server
  sf::Socket::Status stat = socket.connect(IP, port);
  socket.setBlocking(false);
  return stat;
}

sf::Socket::Status Client::send(const std::string& msg) {
  /*sf::Packet packet;
  packet << msg;
  return socket.send(packet);*/

  return socket.send(msg.c_str(), msg.length());
}

sf::Socket::Status Client::receive(std::string& msg) {
  /*sf::Packet packet;
  sf::Socket::Status status = socket.receive(packet);*/
  char buffer[MAX_NET_BUFFER_LENGTH];
  size_t length;
  sf::Socket::Status status =
      socket.receive(buffer, MAX_NET_BUFFER_LENGTH, length);
  if (status == sf::Socket::Done) {
    /*packet >> msg;*/
        msg=buffer;
    std::cout << msg << "\n";
  }
  return status;
}

std::string Client::getName() { return name; }
