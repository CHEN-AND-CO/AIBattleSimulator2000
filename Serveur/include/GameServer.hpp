#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <boost/algorithm/string.hpp>
#include "Server.hpp"
#include <vector>

typedef struct command {
  std::string id, command;
  std::vector<std::string> args;
  int arglen;
} command;

class GameServer {
 public:
  GameServer(const unsigned short port);
  void receive();
  void action(std::string msg);
  command parseCommand(std::string entry);

 private:
  Server server;
  std::string message;
};

#endif /* GAMESERVER_HPP */