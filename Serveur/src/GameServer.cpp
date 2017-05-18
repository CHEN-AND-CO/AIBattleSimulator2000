#include "GameServer.hpp"

GameServer::GameServer(const unsigned short port) {
  listner.listen(port);
  listner.setBlocking(false);
}

void GameServer::receive() {
  receive(message);
  if (message.length() > 0) {
    action(message);
    message.clear();
  }
}

void GameServer::receivePackets(std::string& msg) {
  for (Clients::iterator it = clients.begin(); it != clients.end();) {
    /*sf::Packet packet;
    sf::Socket::Status status = it->second->receive(packet);*/
    char buffer[MAX_NET_BUFFER_LENGTH];
    size_t length;
    sf::Socket::Status status =
        it->second->receive(buffer, MAX_NET_BUFFER_LENGTH, length);

    switch (status) {
      case sf::Socket::Done:
        /*packet >> msg;*/
        msg = buffer;
        std::cout << it->first << ": " << msg << "\n";
        ++it;
        break;

      case sf::Socket::Disconnected:
        std::cout << it->first << " has been disconnected\n";
        it = clients.erase(it);
        break;

      default:
        ++it;
        break;
    }
  }
}

void GameServer::broadCast(const std::string& msg) {
  for (Clients::iterator it = clients.begin(); it != clients.end(); ++it) {
    /*sf::Packet packet;
    packet << msg;

    it->second->send(packet);*/
    it->second->send(msg.c_str(), msg.length());
  }
}

void GameServer::send(const std::string& i, const std::string& msg) {
  /*sf::Packet packet;
  packet << msg;*/
  Clients::iterator tmp = clients.find(i);
  if (tmp == clients.end()) {
    std::cout << "No client found \n";
    return;
  }
  // tmp->second->send(packet);
  tmp->second->send(msg.c_str(), msg.length());
}

void GameServer::receive(std::string& msg) {
  sf::TcpSocket* nextClient = nullptr;

  if (nextClient == nullptr) {
    nextClient = new sf::TcpSocket;
    nextClient->setBlocking(false);
  }
  if (listner.accept(*nextClient) == sf::Socket::Done) {
    clients.insert(std::make_pair(std::to_string(clients.size()), nextClient));
    std::cout << clients.size() - 1 << " is connected\n";
    nextClient = nullptr;
  }

  receivePackets(msg);
}

void GameServer::action(std::string msg) {
  command cmd = parseCommand(msg);
  // printCommand(cmd);
  if (!cmd.command.compare("auth")) {
    authentification(cmd.args, cmd.arglen);
  }
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

void GameServer::authentification(std::vector<std::string> args, int arglen) {
  if (arglen <= 0 && args.size() <= 0) return;
}