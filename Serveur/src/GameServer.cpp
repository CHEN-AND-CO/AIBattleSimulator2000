#include "GameServer.hpp"

GameServer::GameServer(const unsigned short port, std::shared_ptr<Game> gptr)
    : gamePtr{gptr} {
  listner.listen(port);
  listner.setBlocking(false);
}

GameServer::~GameServer() {}

void GameServer::receivePackets() {
  char buffer[MAX_NET_BUFFER_LENGTH];
  size_t length;
  sf::Socket::Status status;
  std::vector<std::map<std::string, std::shared_ptr<sf::TcpSocket>>::iterator>
      list;

  for (auto it = clients.begin(); it != clients.end(); ++it) {
    status = it->second->receive(buffer, MAX_NET_BUFFER_LENGTH, length);

    switch (status) {
      case sf::Socket::Done:
        message = buffer;
        std::cout << it->first << ": " << message << "\n";
        if (message.length() > 0) {
          action(it->first, message, list);
          message.clear();
          for (int i = 0; i < MAX_NET_BUFFER_LENGTH; i++) {
            buffer[i] = 0;
          }
        }
        break;
      case sf::Socket::Disconnected:
        std::cout << it->first << " has been disconnected\n";
        list.push_back(it);
        break;

      default:
        break;
    }
  }

  for (auto i = 0; i < (int)list.size(); i++) {
    clients.erase(list[i]);
  }
}

void GameServer::broadCast(const std::string& msg) {
  for (auto it = clients.begin(); it != clients.end(); ++it) {
    it->second->send(msg.c_str(), msg.length());
  }
}

void GameServer::send(const std::string i, const std::string& msg) {
  auto tmp = clients.find(i);
  if (tmp == clients.end()) {
    std::cout << "No client found \n";
    return;
  }

  if (msg.length() > MAX_NET_BUFFER_LENGTH) {
    std::cout << "Error: Message length is higher than MAX_NET_BUFFER_LENGTH ("
              << MAX_NET_BUFFER_LENGTH << "bytes)\n";
  } else {
    tmp->second->send(msg.c_str(), msg.length());
  }
}

void GameServer::receive() {
  std::shared_ptr<sf::TcpSocket> nextClient = nullptr;

  if (nextClient == nullptr) {
    nextClient = std::make_shared<sf::TcpSocket>();
    nextClient->setBlocking(false);
  }
  if (listner.accept(*nextClient) == sf::Socket::Done) {
    clients.insert(std::make_pair(std::to_string(clients.size()), nextClient));
    send(clients.find(std::to_string(clients.size() - 1))->first,
         std::string(SERVER_ID) + std::string("@auth:1 ") +
             std::to_string(clients.size() - 1));
    std::cout << clients.size() - 1 << " is connected\n";
    nextClient = nullptr;
  }

  receivePackets();
}

void GameServer::action(
    const std::string id, std::string msg,
    std::vector<std::map<
        std::string, std::shared_ptr<sf::TcpSocket>>::iterator>& removelist) {
  command cmd = parseCommand(msg);

  if (!cmd.command.compare("auth")) {
    authentification(id, cmd.args, cmd.arglen, removelist);
  } else if (!cmd.command.compare("getTerrainMap")) {
    if (cmd.arglen < 3) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 getTerrainMap fail"));
      return;
    }
    auto map = gamePtr->getVisibleMap(sf::Color(
        std::atoi(cmd.args[0].c_str()), std::atoi(cmd.args[1].c_str()),
        std::atoi(cmd.args[2].c_str()), 255));
    send(cmd.id, std::string(SERVER_ID) + std::string("@terrain:") +
                     std::to_string(map.size() * map[0].size()) +
                     std::string(" ") + map_to_string(map));
  } else if (!cmd.command.compare("getBuildingsMap")) {
    if (cmd.arglen < 3) {
      send(cmd.id, std::string(SERVER_ID) +
                       std::string("@reply:2 getBuildingsMap fail"));
      return;
    }
    int arglen;
    auto buildings = gamePtr->getVisibleBuildings(sf::Color(
        std::atoi(cmd.args[0].c_str()), std::atoi(cmd.args[1].c_str()),
        std::atoi(cmd.args[2].c_str()), 255));
    std::string args = buildings_to_string(buildings, arglen);
    send(cmd.id, std::string(SERVER_ID) + std::string("@buildings:") +
                     std::to_string(arglen) + std::string(" ") + args);
  } else if (!cmd.command.compare("getEntitysMap")) {
    if (cmd.arglen < 3) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 getEntitysMap fail"));
      return;
    }
    int arglen;
    auto entities = gamePtr->getVisibleEntities(sf::Color(
        std::atoi(cmd.args[0].c_str()), std::atoi(cmd.args[1].c_str()),
        std::atoi(cmd.args[2].c_str()), 255));
    std::string args = entities_to_string(entities, arglen);
    send(cmd.id, std::string(SERVER_ID) + std::string("@entitys:") +
                     std::to_string(arglen) + std::string(" ") + args);
  } else if (!cmd.command.compare("getPlayer")) {
    if (cmd.arglen < 3) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 getPlayer fail"));
      return;
    }
    auto player = gamePtr->getPlayer(sf::Color(
        std::atoi(cmd.args[0].c_str()), std::atoi(cmd.args[1].c_str()),
        std::atoi(cmd.args[2].c_str()), 255));
    int arglen;
    std::string args = playerRessources_to_string(player, arglen);
    send(cmd.id, std::string(SERVER_ID) + std::string("@player:") +
                     std::to_string(arglen) + std::string(" ") + args);
  } else if (!cmd.command.compare("move")) {
    if (cmd.arglen < 5) {
      send(cmd.id, std::string(SERVER_ID) + std::string("@reply:2 move fail"));
      return;
    }
    auto dir = cmd.args[4];
    std::transform(dir.begin(), dir.end(), dir.begin(), ::tolower);
    if (gamePtr->moveEntity(string_to_direction(dir),
                            sf::Color(std::atoi(cmd.args[0].c_str()),
                                      std::atoi(cmd.args[1].c_str()),
                                      std::atoi(cmd.args[2].c_str()), 255),
                            std::atoi(cmd.args[3].c_str()))) {
      send(cmd.id, std::string(SERVER_ID) + std::string("@reply:2 move ok"));
    } else {
      send(cmd.id, std::string(SERVER_ID) + std::string("@reply:2 move fail"));
    }
  } else if (!cmd.command.compare("collect")) {
    if (cmd.arglen < 5) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 collect fail"));
      return;
    }
    auto dir = cmd.args[4];
    std::transform(dir.begin(), dir.end(), dir.begin(), ::tolower);
    if (gamePtr->collectRessource(
            string_to_direction(dir),
            sf::Color(std::atoi(cmd.args[0].c_str()),
                      std::atoi(cmd.args[1].c_str()),
                      std::atoi(cmd.args[2].c_str()), 255),
            std::atoi(cmd.args[3].c_str()))) {
      send(cmd.id, std::string(SERVER_ID) + std::string("@reply:2 collect ok"));
    } else {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 collect fail"));
    }
  } else if (!cmd.command.compare("putInTown")) {
    if (cmd.arglen < 5) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 putInTown fail"));
      return;
    }
    auto dir = cmd.args[4];
    std::transform(dir.begin(), dir.end(), dir.begin(), ::tolower);
    if (gamePtr->putRessourcesInTown(
            string_to_direction(dir),
            sf::Color(std::atoi(cmd.args[0].c_str()),
                      std::atoi(cmd.args[1].c_str()),
                      std::atoi(cmd.args[2].c_str()), 255),
            std::atoi(cmd.args[3].c_str()))) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 putInTown ok"));
    } else {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 putInTown fail"));
    }
  } else if (!cmd.command.compare("attack")) {
    if (cmd.arglen < 5) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 attack fail"));
      return;
    }
    auto dir = cmd.args[4];
    std::transform(dir.begin(), dir.end(), dir.begin(), ::tolower);
    if (gamePtr->attack(sf::Color(std::atoi(cmd.args[0].c_str()),
                                  std::atoi(cmd.args[1].c_str()),
                                  std::atoi(cmd.args[2].c_str()), 255),
                        std::atoi(cmd.args[3].c_str()),
                        string_to_direction(dir))) {
      send(cmd.id, std::string(SERVER_ID) + std::string("@reply:2 attack ok"));
    } else {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 attack fail"));
    }
  } else if (!cmd.command.compare("addEntity")) {
    if (cmd.arglen < 5) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 addEntity fail"));
      return;
    }
    auto ent = cmd.args[4];
    std::transform(ent.begin(), ent.end(), ent.begin(), ::tolower);
    if (gamePtr->addEntity(string_to_entityType(ent),
                           sf::Color(std::atoi(cmd.args[0].c_str()),
                                     std::atoi(cmd.args[1].c_str()),
                                     std::atoi(cmd.args[2].c_str()), 255),
                           std::atoi(cmd.args[3].c_str()))) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 addEntity ok"));
    } else {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 addEntity fail"));
    }
  } else if (!cmd.command.compare("addBuilding")) {
    if (cmd.arglen < 5) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 addBuilding fail"));
      return;
    }
    auto build = cmd.args[4];
    std::transform(build.begin(), build.end(), build.begin(), ::tolower);
    if (gamePtr->addBuilding(string_to_buildingType(build),
                             sf::Color(std::atoi(cmd.args[0].c_str()),
                                       std::atoi(cmd.args[1].c_str()),
                                       std::atoi(cmd.args[2].c_str()), 255),
                             std::atoi(cmd.args[3].c_str()))) {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 addBuilding ok"));
    } else {
      send(cmd.id,
           std::string(SERVER_ID) + std::string("@reply:2 addBuilding fail"));
    }
  } else {
    send(cmd.id, std::string(SERVER_ID) + std::string("@reply:2 ") +
                     cmd.command + std::string(" fail"));
  }
  printCommand(cmd);
}

command GameServer::parseCommand(std::string entry) {
  command out;
  out.command = "";
  out.id = "";

  std::vector<std::string> tmp;
  std::string stmp;

  // boost::split(tmp, entry, boost::is_any_of(" "));  // Split every space
  tmp = split(entry, ' ');
  stmp = tmp[0];
  tmp.erase(tmp.begin());
  out.args = tmp;
  tmp.clear();

  // boost::split(tmp, stmp, boost::is_any_of("@"));  // Split every @
  tmp = split(stmp, '@');
  if (tmp.size() > 0) out.id = tmp[0];
  if (tmp.size() > 1) out.command = tmp[1];
  tmp.clear();

  // boost::split(tmp, out.command, boost::is_any_of(":"));  // Split every :
  tmp = split(out.command, ':');
  if (tmp.size() > 0) out.command = tmp[0];
  if (tmp.size() > 1) out.arglen = std::atoi(tmp[1].c_str());
  tmp.clear();

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

void GameServer::clearCommand(command& cmd) {
  cmd.args.clear();
  cmd.arglen = -1;
  cmd.command.clear();
  cmd.id.clear();
  cmd.valid = false;
}

void GameServer::authentification(
    const std::string id, std::vector<std::string> args, int arglen,
    std::vector<std::map<
        std::string, std::shared_ptr<sf::TcpSocket>>::iterator>& removelist) {
  if (arglen <= 0 && args.size() <= 0) return;
  if (clients.find(args[0]) != clients.end() &&
      clients.find(id) == clients.end()) {
    send(id, std::string(SERVER_ID) + std::string("@auth:1 fail"));
  } else {
    clients.insert(std::make_pair(args[0], clients.find(id)->second));
    removelist.push_back(clients.find(id));
    send(clients.find(args[0])->first,
         std::string(SERVER_ID) + std::string("@auth:1 ok"));
  }
}

std::vector<std::string> GameServer::split(const std::string& in,
                                           const char& token) {
  std::vector<std::string> out;
  std::string buffer = "";
  for (auto n : in) {
    if (n != token)
      buffer += n;
    else if (n == token && buffer != "") {
      out.push_back(buffer);
      buffer = "";
    }
  }
  if (buffer != "") out.push_back(buffer);

  return out;
}

std::string GameServer::map_to_string(std::vector<std::vector<int>> map) {
  std::string out;
  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map[0].size(); j++) {
      out += std::to_string(map[i][j]) + std::string(" ");
    }
  }
  out.pop_back();

  return out;
}

std::string GameServer::buildings_to_string(std::vector<Building> buildings,
                                            int& argn) {
  std::string out;
  argn = 0;

  for (auto i : buildings) {
    out += building_to_string(i);
    argn += 7;
  }
  out.pop_back();

  return out;
}

std::string GameServer::entities_to_string(std::vector<Entity> entities,
                                           int& argn) {
  std::string out;
  argn = 0;

  for (auto i : entities) {
    out += entity_to_string(i);
    argn += 7;
  }
  out.pop_back();

  return out;
}

std::string GameServer::playerRessources_to_string(Player player, int& argn) {
  std::string out;
  argn = 0;
  std::map<Ressource, int> ressources = player.getRessources();
  for (auto i = ressources.begin(); i != ressources.end(); ++i) {
    out += RessourceType_to_string(i->first) + std::string(" ");
    out += std::to_string(i->second) + std::string(" ");
  }
  out.pop_back();

  return out;
}

std::string GameServer::building_to_string(Building building) {
  std::string out;
  out += std::to_string(building.getPosition().x) + std::string(" ");  // x
  out += std::to_string(building.getPosition().y) + std::string(" ");  // y

  out += std::to_string(building.getColor().r) + std::string(" ");  // r
  out += std::to_string(building.getColor().g) + std::string(" ");  // g
  out += std::to_string(building.getColor().b) + std::string(" ");  // b

  out += std::to_string(building.getHealth()) + std::string(" ");  // hp

  out += buildingType_to_string(building.getType()) + std::string(" ");  // type

  return out;
}

std::string GameServer::buildingType_to_string(BuildingType type) {
  if (type == BuildingType::TownCenter) {
    return "TownCenter";
  } else if (type == BuildingType::Fort) {
    return "Fort";
  } else if (type == BuildingType::MaxBuildingType) {
    return "MaxBuildingType";
  } else {
    return "";
  }
}

std::string GameServer::entity_to_string(Entity entity) {
  std::string out;
  out += std::to_string(entity.getPosition().x) + std::string(" ");  // x
  out += std::to_string(entity.getPosition().y) + std::string(" ");  // y

  out += std::to_string(entity.getColor().r) + std::string(" ");  // r
  out += std::to_string(entity.getColor().g) + std::string(" ");  // g
  out += std::to_string(entity.getColor().b) + std::string(" ");  // b

  out += std::to_string(entity.getHealth()) + std::string(" ");  // hp

  out += entityType_to_string(entity.getType()) + std::string(" ");  // type

  return out;
}
std::string GameServer::entityType_to_string(EntityType type) {
  if (type == EntityType::Villager) {
    return "Villager";
  } else if (type == EntityType::Warrior) {
    return "Warrior";
  } else if (type == EntityType::Horse) {
    return "Horse";
  } else if (type == EntityType::MaxEntityType) {
    return "MaxEntityType";
  } else {
    return "";
  }
}

std::string GameServer::RessourceType_to_string(Ressource ressource) {
  if (Ressource::Wood == ressource) {
    return "Wood";
  } else if (Ressource::Food == ressource) {
    return "Food";
  } else if (Ressource::Gold == ressource) {
    return "Gold";
  } else if (Ressource::MaxRessources == ressource) {
    return "MaxRessources";
  } else {
    return "";
  }
}

Direction GameServer::string_to_direction(std::string dir) {
  if (!dir.compare("up")) {
    return Direction::Up;
  }
  if (!dir.compare("down")) {
    return Direction::Down;
  }
  if (!dir.compare("left")) {
    return Direction::Left;
  }
  if (!dir.compare("right")) {
    return Direction::Right;
  }
  return Direction::MaxDirection;
}

EntityType GameServer::string_to_entityType(std::string ent) {
  if (!ent.compare("villager")) {
    return EntityType::Villager;
  }
  if (!ent.compare("warrior")) {
    return EntityType::Warrior;
  }
  if (!ent.compare("horse")) {
    return EntityType::Horse;
  }
  return EntityType::MaxEntityType;
}

BuildingType GameServer::string_to_buildingType(std::string build) {
  if (!build.compare("towncenter")) {
    return BuildingType::TownCenter;
  }
  if (!build.compare("fort")) {
    return BuildingType::Fort;
  }
  if (!build.compare("stable")) {
    return BuildingType::Stable;
  }
  return BuildingType::MaxBuildingType;
}
