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

#ifndef SERVER_ID
#define SERVER_ID "SERVER"
#endif /* SERVER_ID */

typedef struct command {
  std::string id, command;
  std::vector<std::string> args;
  int arglen;
  bool valid;
} command;

typedef std::unordered_map<std::string, sf::TcpSocket*> Clients;

class GameServer {
 public:
  GameServer(const unsigned short port);

  void receive();
  void send(const std::string i, const std::string& msg);
  void broadCast(const std::string& msg);
  void receivePackets();

  void action(const std::string id, std::string msg);
  command parseCommand(std::string entry);
  void printCommand(command cmd);
  void clearCommand(command& cmd);
  void authentification(const std::string id, std::vector<std::string> args,
                        int arglen);
  std::vector<std::string> split(const std::string& in, const char& token);

 private:
  std::string message;
  Clients clients;
  sf::TcpListener listner;
};

#endif /* GAMESERVER_HPP */