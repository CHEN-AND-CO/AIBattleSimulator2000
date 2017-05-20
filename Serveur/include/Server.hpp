#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Network.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Client.hpp"

#ifndef MAX_NET_BUFFER_LENGTH
#define MAX_NET_BUFFER_LENGTH 65536
#endif /* MAX_NET_BUFFER_LENGTH */

class Server {
 public:
  Server(const unsigned short port);

  void receive(std::string &msg);
  void send(const std::string &i, const std::string &msg);
  void broadCast(const std::string &msg);
  void receivePackets(std::string &msg);

 private:
  typedef std::unordered_map<std::string, sf::TcpSocket *> Clients;
  Clients clients;
  sf::TcpListener listner;
};

#endif /* SERVER_HPP */