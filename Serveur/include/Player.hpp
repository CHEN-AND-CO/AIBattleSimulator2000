#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Building.hpp"
#include "Entity.hpp"

class Player {
 public:
  Player(const sf::Color& col, const sf::Vector2f& pos);

  std::vector<Building> getBuildings() const { return mBuildings; }
  std::vector<Entity> getEntities() const { return mEntities; }
  sf::Color getColor() const { return mColor; }

  void addEntity(const EntityType& entT, const sf::Color& col,
                 const sf::Vector2f& pos);
  void addBuilding(const BuildingType& buildT, const sf::Color& col,
                   const sf::Vector2f& pos);

  void moveEntity(Direction dir, const Game& game, int i) {
    mEntities[i].move(dir, game);
  }

  void clearMaps();

 private:
  std::vector<Building> mBuildings;
  std::vector<Entity> mEntities;
  sf::Color mColor;
  int mWood;
  int mEntID, mBuildID;
};

#endif
