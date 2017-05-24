#include "Player.hpp"
#include <iostream>
#include "Game.hpp"

Player::Player(const Game& game, const sf::Color& col, const sf::Vector2f& pos,
               unsigned mapSize)
    : mColor{col}, mEntID{0}, mBuildID{0}, mBuildingView{4}, mEntityView{2} {
  for (unsigned i{0}; i < mapSize; i++) {
    mCache.push_back(std::vector<int>(mapSize));
    for (unsigned j{0}; j < mapSize; j++) {
      mCache[i][j] = 0;
    }
  }

  mRessources[Ressource::Wood] = 650;
  addBuilding(game, BuildingType::TownCenter, pos);
  addEntity(game, EntityType::Villager, pos + sf::Vector2f(2, 0));
}

void Player::clearMaps() {
  std::vector<int> index;
  for (unsigned i{0}; i < mBuildings.size(); i++) {
    if (!mBuildings[i].isAlive()) {
      index.push_back(i);
    }
  }
  for (auto i : index) {
    mBuildings.erase(mBuildings.begin() + i);
  }

  index.clear();

  for (unsigned i{0}; i < mEntities.size(); i++) {
    if (!mEntities[i].isAlive()) {
      index.push_back(i);
    }
  }
  for (auto i : index) {
    mEntities.erase(mEntities.begin() + i);
  }
}

bool Player::addEntity(const Game& game, const EntityType& entT,
                       const sf::Vector2f& pos) {
  if (game.getMap()[pos.y][pos.x] != 1) {
    std::cout << "Postion obstructed" << std::endl;
    return false;
  }
  for (const auto& ent : game.getEntities()) {
    if (rectCollide(pos, ent.getPosition())) {
      std::cout << "Postion obstructed" << std::endl;
      return false;
    }
  }
  for (const auto& build : game.getBuildings()) {
    if (rectCollide(build.getPosition(), build.getSize(), pos,
                    sf::Vector2f(1, 1))) {
      std::cout << "Postion obstructed" << std::endl;
      return false;
    }
  }
  switch (entT) {
    case EntityType::Villager:
      if (mRessources[Ressource::Wood] < 50) {
        std::cout << "Not enough ressources to create Villager\n";
        return false;
      } else {
        mEntities.push_back(Entity(entT, mColor, pos, mEntID++));
        mRessources[Ressource::Wood] -= 50;
      }
      break;
    case EntityType::Warrior:
      if (mRessources[Ressource::Wood] < 60) {
        std::cout << "Not enough ressources to create Warrior\n";
        return false;
      } else {
        mEntities.push_back(Entity(entT, mColor, pos, mEntID++));
        mRessources[Ressource::Wood] -= 60;
      }
      break;
    default:
      return false;
      break;
  }
  return true;
}

bool Player::addBuilding(const Game& game, const BuildingType& buildT,
                         const sf::Vector2f& pos) {
  if (game.getMap()[pos.y][pos.x] != 1) {
    std::cout << "Postion obstructed" << std::endl;
    return false;
  }
  for (const auto& ent : game.getEntities()) {
    if (rectCollide(pos, ent.getPosition())) {
      std::cout << "Postion obstructed" << std::endl;
      return false;
    }
  }
  for (const auto& build : game.getBuildings()) {
    if (rectCollide(build.getPosition(), build.getSize(), pos,
                    sf::Vector2f(1, 1))) {
      std::cout << "Postion obstructed" << std::endl;
      return false;
    }
  }
  switch (buildT) {
    case BuildingType::TownCenter:
      if (mRessources[Ressource::Wood] < 600) {
        std::cout << "Not enough ressources to construct Town\n";
        return false;
      } else {
        mBuildings.push_back(Building(buildT, mColor, pos, mBuildID++));
        mRessources[Ressource::Wood] -= 600;
      }
      break;
    case BuildingType::Fort:
      if (mRessources[Ressource::Wood] < 200) {
        std::cout << "Not enough ressources to construct Fort\n";
        return false;
      } else {
        mBuildings.push_back(Building(buildT, mColor, pos, mBuildID++));
        mRessources[Ressource::Wood] -= 200;
      }
    default:
      return false;
      break;
  }
  return true;
}

void Player::updateCache() {
  for (const auto& b : mBuildings) {
    sf::Vector2f pos = b.getPosition();
    for (int x{-mBuildingView}; x <= mBuildingView; x++) {
      for (int y{-mBuildingView}; y <= mBuildingView; y++) {
        sf::Vector2f checkPos = pos + sf::Vector2f(x, y);
        if (checkPos.x < 0 || checkPos.y < 0 ||
            checkPos.x >= mCache[0].size() || checkPos.y >= mCache.size()) {
          continue;
        }
        mCache[checkPos.y][checkPos.x] = 1;
      }
    }
  }

  for (const auto& e : mEntities) {
    sf::Vector2f pos = e.getPosition();
    for (int x{-mBuildingView}; x <= mBuildingView; x++) {
      for (int y{-mBuildingView}; y <= mBuildingView; y++) {
        sf::Vector2f checkPos = pos + sf::Vector2f(x, y);
        if (checkPos.x < 0 || checkPos.y < 0 ||
            checkPos.x >= mCache[0].size() || checkPos.y >= mCache.size()) {
          continue;
        }
        mCache[checkPos.y][checkPos.x] = 1;
      }
    }
  }
}
