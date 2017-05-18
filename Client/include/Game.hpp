#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Client.hpp"

/*
                CONVENTION MAP

1: Herbe, Franchissable
2: Foret, Infranchissable, Ressource
3: Riviere, Infranchissable
*/

struct Building{
  sf::Vector2f mPosisiton;
  sf::Color mColor;
  BuildingType mType;
};

class Game {
 public:
  Game(const sf::IpAddress& ip, unsigned short port, std::string name);
  std::vector<std::vector<int>> getMap();

 private:
  Client mClient;
};

#endif

//   std::vector<Player> getPlayer() const { return mPlayer; }
//   std::vector<Building> getBuildings() const;
//   std::vector<Entity> getEntities() const;
//   Player getPlayer(const sf::Color&) const;
//   std::vector<Building> getBuildings(const sf::Color&) const;
//   std::vector<Entity> getEntities(const sf::Color&) const;
//   bool addEntity(const EntityType& entT, const sf::Color& col, int index)
//   bool addBuilding(const BuildingType& buildT, const sf::Color& col, int
//   index)
//   bool addPlayer(const sf::Color& col, const sf::Vector2f pos)
//   bool moveEntity(const Direction& dir, const sf::Color& col, int i)
//   bool collectRessource(const Direction& dir, const sf::Color& col, int
//   index)
//   bool putRessourcesInTown(const Direction& dir, const sf::Color& col,
//                            int index)
//   bool attack(const sf::Color& col1, int index1);
//   bool isGameFinish() const;
//   sf::Color getWinner() const;
