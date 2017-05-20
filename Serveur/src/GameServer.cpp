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
  printCommand(cmd);
}

command GameServer::parseCommand(std::string entry) {
  command out;
  out.command = "";
  out.id = "";

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

  if (out.id.length() < 1 || out.command.length() < 1 || out.arglen < 0) {
    out.valid = false;
  } else {
    out.valid = true;
  }

  return out;
}

void GameServer::printCommand(command cmd) {
  if (cmd.valid) {
    std::cout << "id : " << cmd.id << std::endl;
    std::cout << "command : " << cmd.command << std::endl;
    std::cout << "arglen : " << cmd.arglen << std::endl;
    for (auto& ref : cmd.args) {
      std::cout << ref << "\t";
    }
    std::cout << std::endl;
  } else {
    std::cout << "Not a valid Command format\n";
  }
}