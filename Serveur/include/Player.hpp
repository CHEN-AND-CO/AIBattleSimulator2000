#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Building.hpp"
#include "Entity.hpp"

class Player {
 public:
<<<<<<< HEAD
  Player(const Game& game, const sf::Color& col, const sf::Vector2f& pos,
         buildMap ressourceB, entMap ressourceE, unsigned mapSize);
  
=======
  Player(const sf::Color& col, const sf::Vector2f& pos);

>>>>>>> origin/advancedServerImplement
  std::vector<Building> getBuildings() const { return mBuildings; }
  std::vector<Entity> getEntities() const { return mEntities; }
  sf::Color getColor() const { return mColor; }
  std::map<Ressource, int> getRessources() { return mRessources; }
  int getRessources(Ressource r) { return mRessources[r]; }

<<<<<<< HEAD
  std::vector<std::vector<int>> getCache() const { return mCache; }

  bool addEntity(const Game& game, const EntityType& entT,
                 const sf::Vector2f& pos, entMap ressourceMap);
  bool addBuilding(const Game& game, const BuildingType& buildT,
                   const sf::Vector2f& pos, buildMap ressourceMap);
  bool addBuilding(const Game& game, const BuildingType& buildT, int index,
                   buildMap ressourceMap) {
    return mEntities[index].addBuilding(game, *this, buildT, ressourceMap);
  }
  bool addEntity(const Game& game, const EntityType& entT, int index,
                 entMap ressourceMap) {
    return mBuildings[index].addEntity(game, *this, entT, ressourceMap);
=======
  void addEntity(const EntityType& entT, const sf::Vector2f& pos);
  void addBuilding(const BuildingType& buildT, const sf::Vector2f& pos);
  void addBuilding(const BuildingType& buildT, int index) {
    mEntities[index].addBuilding(*this, buildT);
  }
  void addEntity(const EntityType& entT, int index) {
    mBuildings[index].addEntity(*this, entT);
>>>>>>> origin/advancedServerImplement
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
<<<<<<< HEAD
  void updateCache();
=======
>>>>>>> origin/advancedServerImplement

 private:
  std::vector<Building> mBuildings;
  std::vector<Entity> mEntities;
<<<<<<< HEAD
  std::vector<std::vector<int>> mCache;
  sf::Color mColor;
  std::map<Ressource, int> mRessources;
  int mEntID, mBuildID;
  int mBuildingView, mEntityView;
=======
  sf::Color mColor;
  std::map<Ressource, int> mRessources;
  int mEntID, mBuildID;
>>>>>>> origin/advancedServerImplement
};

#endif
