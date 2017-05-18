#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <SFML/Network.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "Client.hpp"

#ifndef MAX_NET_BUFFER_LENGTH
#define MAX_NET_BUFFER_LENGTH 65536
#endif /* MAX_NET_BUFFER_LENGTH */

typedef struct command {
  std::string id, command;
  std::vector<std::string> args;
  int arglen;
  bool valid;
} command;

class GameServer {
 public:
  GameServer(const unsigned short port);
  void receive();
  
  void receive(std::string &msg);
  void send(const std::string &i, const std::string &msg);
  void broadCast(const std::string &msg);
  void receivePackets(std::string &msg);

  void action(std::string msg);
  command parseCommand(std::string entry);
  void printCommand(command cmd);
  void authentification( std::vector<std::string> args, int arglen );

 private:
  std::string message;

  typedef std::unordered_map<std::string, sf::TcpSocket *> Clients;
  Clients clients;
  sf::TcpListener listner;
};

#endif /* GAMESERVER_HPP */