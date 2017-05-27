#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Network.hpp>
#include <iostream>

class Client {
 private:
  std::string name;
  sf::TcpSocket socket;

 public:
  Client(const std::string cname);

  sf::Socket::Status connect(const sf::IpAddress& IP, unsigned short port);
  sf::Socket::Status send(const std::string& msg);
  sf::Socket::Status receive(std::string& msg);
  std::string getName();
};

#endif /* CLIENT_HPP */