#include "Player.hpp"
#include <iostream>

Player::Player(const sf::Color& col, const sf::Vector2f& pos, unsigned mapSize)
    : mColor{col}, mEntID{0}, mBuildID{0}, mBuildingView{4}, mEntityView{2} {
  for (unsigned i{0}; i < mapSize; i++) {
    mCache.push_back(std::vector<int>(mapSize));
    for (unsigned j{0}; j < mapSize; j++) {
      mCache[i][j] = 0;
    }
  }

  mRessources[Ressource::Wood] = 650;
  addBuilding(BuildingType::TownCenter, pos);
  addEntity(EntityType::Villager, pos + sf::Vector2f(2, 0));
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

void Player::addEntity(const EntityType& entT, const sf::Vector2f& pos) {
  switch (entT) {
    case EntityType::Villager:
      if (mRessources[Ressource::Wood] < 50) {
        std::cout << "Not enough ressources to create Villager\n";
      } else {
        mEntities.push_back(Entity(entT, mColor, pos, mEntID++));
        mRessources[Ressource::Wood] -= 50;
      }
      break;
    case EntityType::Warrior:
      if (mRessources[Ressource::Wood] < 60) {
        std::cout << "Not enough ressources to create Warrior\n";
      } else {
        mEntities.push_back(Entity(entT, mColor, pos, mEntID++));
        mRessources[Ressource::Wood] -= 60;
      }
      break;
    default:
      break;
  }
  updateCache();
}

void Player::addBuilding(const BuildingType& buildT, const sf::Vector2f& pos) {
  switch (buildT) {
    case BuildingType::TownCenter:
      if (mRessources[Ressource::Wood] < 600) {
        std::cout << "Not enough ressources to construct Town\n";
      } else {
        mBuildings.push_back(Building(buildT, mColor, pos, mBuildID++));
        mRessources[Ressource::Wood] -= 600;
      }
      break;
    case BuildingType::Fort:
      if (mRessources[Ressource::Wood] < 200) {
        std::cout << "Not enough ressources to construct Fort\n";
      } else {
        mBuildings.push_back(Building(buildT, mColor, pos, mBuildID++));
        mRessources[Ressource::Wood] -= 200;
      }
    default:
      break;
  }
  updateCache();
}

void Player::updateCache() {
  for (const auto& b : mBuildings) {
    sf::Vector2f pos = b.getPosition();
    for (int x{-mBuildingView}; x <= mBuildingView + b.getSize().x; x++) {
      for (int y{-mBuildingView}; y <= mBuildingView + b.getSize().y; y++) {
        if (!(x + pos.x >= 0 && y + pos.y >= 0 &&
              x + pos.x < mCache[0].size() && y + pos.y < mCache.size())) {
          mCache[y + pos.y][x + pos.x] = 1;
        }
      }
    }
  }

  for (const auto& e : mEntities) {
    sf::Vector2f pos = e.getPosition();
    for (int x{-mBuildingView}; x <= mBuildingView; x++) {
      for (int y{-mBuildingView}; y <= mBuildingView; y++) {
        mCache[y + pos.y][x + pos.x] = 1;
      }
    }
  }
}
