#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Client.hpp"
#include "Define.hpp"

/*
                CONVENTION MAP

1: Herbe, Franchissable
2: Foret, Infranchissable, Ressource
3: Riviere, Infranchissable
*/

struct Building {
  sf::Vector2f mPositon;
  sf::Color mColor;
  int hp;
  BuildingType mType;
};

struct Entity {
  sf::Vector2f mPositon;
  sf::Color mColor;
  int hp;
  EntityType mType;
};

struct Player {
  std::map<Ressource, int> mRessources;
  sf::Color mColor;
};

class Game {
 public:
  Game(const sf::IpAddress& ip, unsigned short port, std::string name, const sf::Color& col);
  std::vector<std::vector<int>> getMap(const sf::Color& col);
  std::vector<Building> getBuildings(const sf::Color& col);
  std::vector<Entity> getEntities(const sf::Color& col);
  Player getPlayer(const sf::Color& col);

  bool attack(const Direction& dir, const sf::Color& col, int index);
  bool moveEntity(const Direction& dir, const sf::Color& col, int index);
  bool collectRessource(const Direction& dir, const sf::Color& col, int index);
  bool putRessourcesInTown(const Direction& dir, const sf::Color& col,
                           int index);
  bool addEntity(const EntityType& entT, const sf::Color& col, int index);
  bool addBuilding(const BuildingType& buildT, const sf::Color& col, int index);

 private:
  Client mClient;
};

#endif

