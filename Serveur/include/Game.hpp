#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "Building.hpp"
#include "Entity.hpp"

/*
                CONVENTION MAP

1: Herbe, Franchissable
2: Foret, Infranchissable, Ressource
3: Riviere, Infranchissable
*/

class Game {
  template <typename T>  // define a vector of vector
  using dVector = typename std::vector<std::vector<T>>;

 public:
  bool loadFile(const std::string& fileName);

  dVector<int> getMap() const { return mMap; }
  std::vector<Building> getBuildings() const { return mBuilding; }
  std::vector<Entity> getEntities() const { return mEntities; }

  void addEntity(const EntityType& entT, const sf::Color& col,
                 const sf::Vector2f& pos) {
    mEntities.push_back(Entity(entT, col, pos));
  }

  void addBuilding(const BuildingType& entT, const sf::Color& col,
                   const sf::Vector2f& pos) {
    mBuilding.push_back(Building(entT, col, pos));
  }

  bool isGameFinish() const;
  sf::Color getWinner() const;

 private:
  dVector<int> mMap;
  std::vector<Building> mBuilding;
  std::vector<Entity> mEntities;
};

#endif
