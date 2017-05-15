#include "Player.hpp"
#include <iostream>

Player::Player(const sf::Color& col, const sf::Vector2f& pos)
    : mColor{col}, mEntID{0}, mBuildID{0} {
  mRessources[Ressource::Wood] = 600;
  addBuilding(BuildingType::TownCenter, mColor, pos);
  addEntity(EntityType::Villager, mColor, pos + sf::Vector2f(2, 0));
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

void Player::addEntity(const EntityType& entT, const sf::Color& col,
                       const sf::Vector2f& pos) {
  mEntities.push_back(Entity(entT, col, pos, mEntID++));
}

void Player::addBuilding(const BuildingType& buildT, const sf::Color& col,
                         const sf::Vector2f& pos) {
  switch (buildT) {
    case BuildingType::TownCenter:
      if (mRessources[Ressource::Wood] < 600) {
        std::cout << "Not enought ressources to construct Town\n";
      } else {
        mBuildings.push_back(Building(buildT, col, pos, mBuildID++));
        mRessources[Ressource::Wood] -= 600;
      }
      break;
    case BuildingType::Fort:
      if (mRessources[Ressource::Wood] < 200) {
        std::cout << "Not enought ressources to construct Fort\n";
      } else {
        mBuildings.push_back(Building(buildT, col, pos, mBuildID++));
        mRessources[Ressource::Wood] -= 200;
      }
    default:
      break;
  }
}
