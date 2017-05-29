#ifndef GAMESERVER_HPP
#define GAMESERVER_HPP

#include <SFML/Network.hpp>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
//#include <boost/algorithm/string.hpp>

#include "Client.hpp"

#include "Game.hpp"

#ifndef MAX_NET_BUFFER_LENGTH
#define MAX_NET_BUFFER_LENGTH 65536
#endif /* MAX_NET_BUFFER_LENGTH */

#ifndef SERVER_ID
#define SERVER_ID "SERVER"
#endif /* SERVER_ID */

struct command {
  std::string id, command;
  std::vector<std::string> args;
  int arglen;
  bool valid;
};

class GameServer {
 public:
  GameServer(const unsigned short port, std::shared_ptr<Game> gptr);
  ~GameServer();

  void receive();
  void send(const std::string i, const std::string& msg);
  void broadCast(const std::string& msg);
  void receivePackets();

  void action(
      const std::string id, std::string msg,
      std::vector<std::map<
          std::string, std::shared_ptr<sf::TcpSocket>>::iterator>& removelist);
  command parseCommand(std::string entry);
  void printCommand(command cmd);
  void clearCommand(command& cmd);
  void authentification(
      const std::string id, std::vector<std::string> args, int arglen,
      std::vector<std::map<
          std::string, std::shared_ptr<sf::TcpSocket>>::iterator>& removelist);

  std::vector<std::string> split(const std::string& in, const char& token);

  std::string map_to_string(std::vector<std::vector<int>> map);
  std::string buildings_to_string(std::vector<Building> buildings, int& argn);
  std::string entities_to_string(std::vector<Entity> entities, int& argn);
  std::string playerRessources_to_string(Player player, int& argn );

  std::string building_to_string(Building building);
  std::string buildingType_to_string(BuildingType type);
  std::string entity_to_string(Entity entity);
  std::string entityType_to_string(EntityType type);
  std::string RessourceType_to_string(Ressource ressource);
  
  Direction string_to_direction(std::string dir);
  EntityType string_to_entityType(std::string ent);
  BuildingType string_to_buildingType(std::string build);

 private:
  std::string message;
  std::map<std::string, std::shared_ptr<sf::TcpSocket>> clients;
  std::shared_ptr<Game> gamePtr;
  sf::TcpListener listner;
};

#endif /* GAMESERVER_HPP */
