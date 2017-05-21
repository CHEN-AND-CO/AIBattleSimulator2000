#ifndef SERVER_HPP
#define SERVER_HPP

#include <unordered_map>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include "Client.hpp"

class Server {
 public:
  Server(unsigned short port);

  void receive();
  void broadCast(const std::string &msg);
  void receivePackets();

 private:
  typedef std::unordered_map<sf::TcpSocket *, std::string> Clients;
  Clients clients;
  sf::TcpListener listner;
};

#endif /* SERVER_HPP */