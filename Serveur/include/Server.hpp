#ifndef SERVER_HPP
#define SERVER_HPP

#include <unordered_map>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include "Client.hpp"

class Server {
 public:
  Server( const unsigned short port);

  void receive();
  void send( const std::string& i, const std::string& msg );
  void broadCast(const std::string &msg);
  void receivePackets();

 private:
  typedef std::unordered_map<std::string, sf::TcpSocket *> Clients;
  Clients clients;
  sf::TcpListener listner;
};

#endif /* SERVER_HPP */