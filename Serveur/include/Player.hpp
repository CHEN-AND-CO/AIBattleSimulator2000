#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Building.hpp"
#include "Entity.hpp"

class Player {
 public:
  Player(const Game& game, const sf::Color& col, const sf::Vector2f& pos,
         unsigned mapSize);

  std::vector<Building> getBuildings() const { return mBuildings; }
  std::vector<Entity> getEntities() const { return mEntities; }
  sf::Color getColor() const { return mColor; }
  std::map<Ressource, int> getRessources() { return mRessources; }
  int getRessources(Ressource r) { return mRessources[r]; }

  std::vector<std::vector<int>> getCache() const { return mCache; }

  bool addEntity(const Game& game, const EntityType& entT,
                 const sf::Vector2f& pos);
  bool addBuilding(const Game& game, const BuildingType& buildT,
                   const sf::Vector2f& pos);
  bool addBuilding(const Game& game, const BuildingType& buildT, int index) {
    return mEntities[index].addBuilding(game, *this, buildT);
  }
  bool addEntity(const Game& game, const EntityType& entT, int index) {
    return mBuildings[index].addEntity(game, *this, entT);
  }

  bool moveEntity(Direction dir, const Game& game, int i) {
    return mEntities[i].move(dir, game);
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
