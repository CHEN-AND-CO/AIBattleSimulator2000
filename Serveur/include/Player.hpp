#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Building.hpp"
#include "Entity.hpp"

class Player {
 public:
  Player(const sf::Color& col, const sf::Vector2f& pos, unsigned mapSize);

  std::vector<Building> getBuildings() const { return mBuildings; }
  std::vector<Entity> getEntities() const { return mEntities; }
  sf::Color getColor() const { return mColor; }
  std::map<Ressource, int> getRessources() { return mRessources; }
  int getRessources(Ressource r) { return mRessources[r]; }

  std::vector<std::vector<int>> getCache() const { return mCache; }

  void addEntity(const EntityType& entT, const sf::Vector2f& pos);
  void addBuilding(const BuildingType& buildT, const sf::Vector2f& pos);
  void addBuilding(const BuildingType& buildT, int index) {
    mEntities[index].addBuilding(*this, buildT);
  }
  void addEntity(const EntityType& entT, int index) {
    mBuildings[index].addEntity(*this, entT);
  }

  bool moveEntity(Direction dir, const Game& game, int i) {
    auto result = mEntities[i].move(dir, game);
    updateCache();
    return result;
  }

  void addRessource(Ressource r, int val) { mRessources[r] += val; }

  bool collectRessource(const Game& game, Direction dir, int index) {
    return mEntities[index].collectRessource(game, *this, dir);
  }

  bool putRessourcesInTown(int index) {
    return mEntities[index].putRessourcesInTown(*this);
  }

  void receiveDamageEntity(int damage, int index) {
    mEntities[index].receiveDamage(damage);
  }
  void receiveDamageBuilding(int damage, int index) {
    mBuildings[index].receiveDamage(damage);
  }

  void clearMaps();
  void updateCache();

 private:
  std::vector<Building> mBuildings;
  std::vector<Entity> mEntities;
  std::vector<std::vector<int>> mCache;
  sf::Color mColor;
  std::map<Ressource, int> mRessources;
  int mEntID, mBuildID;
  int mBuildingView, mEntityView;
};

#endif
