#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include <iostream>

#ifndef MAX_NET_BUFFER_LENGTH
#define MAX_NET_BUFFER_LENGTH 65536
#endif /* MAX_NET_BUFFER_LENGTH */

class Client {
 private:
  std::string mName;
  sf::TcpSocket mSocket;

 public:
  Client(const std::string name) : mName{name} {}

  sf::Socket::Status connect(const sf::IpAddress& IP, unsigned short port);
  sf::Socket::Status send(const std::string& msg);
  std::string receive();
  std::string getName() { return mName; }
};

#endif /* CLIENT_HPP */