#include "GameServer.hpp"

GameServer::GameServer(const unsigned short port) : server(port) {}

void GameServer::receive() {
  server.receive(message);
  if (message.length() > 0) {
    action(message);
    message.clear();
  }
}

void GameServer::action(std::string msg) {
  command cmd = parseCommand(msg);

  std::cout << "id : " << cmd.id << std::endl;
  std::cout << "command : " << cmd.command << std::endl;
  std::cout << "arglen : " << cmd.arglen << std::endl;
}

command GameServer::parseCommand(std::string entry) {
  command out;
  std::vector<std::string> tmp;
  std::string stmp;

  boost::split(tmp, entry, boost::is_any_of(" "));  // Split every space
  stmp = tmp[0];
  tmp.erase(tmp.begin());
  out.args = tmp;
  tmp.clear();

  boost::split(tmp, stmp, boost::is_any_of("@"));  // Split every @
  if (tmp.size() > 0) out.id = tmp[0];
  if (tmp.size() > 1) out.command = tmp[1];
  tmp.clear();

  boost::split(tmp, out.command, boost::is_any_of(":"));  // Split every :
  if (tmp.size() > 0) out.command = tmp[0];
  if (tmp.size() > 1) out.arglen = std::atoi(tmp[1].c_str());

  return out;
}