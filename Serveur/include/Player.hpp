#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Building.hpp"
#include "Entity.hpp"

class Player {
 public:
  Player(sf::Color col) : mColor{col} {}
  std::vector<Building> getBuildings() const { return mBuilding; }
  std::vector<Entity> getEntities() const { return mEntities; }
  sf::Color getColor() const { return mColor; }

  void addEntity(const EntityType& entT, const sf::Color& col,
                 const sf::Vector2f& pos) {
    mEntities.push_back(Entity(entT, col, pos));
  }

  void addBuilding(const BuildingType& entT, const sf::Color& col,
                   const sf::Vector2f& pos) {
    mBuilding.push_back(Building(entT, col, pos));
  }

 private:
  std::vector<Building> mBuilding;
  std::vector<Entity> mEntities;
  sf::Color mColor;
};

#endif
