#include "Building.hpp"
#include <iostream>
#include "Entity.hpp"
#include "Game.hpp"
#include "Player.hpp"

/*
Function which create an entity if this building can create it
depending of the types of both of them
*/

Building::Building(BuildingType bT, sf::Color color, sf::Vector2f pos, int id)
    : mType{bT}, mColor{color}, mPos{pos}, mHealth{1000}, mID{id} {
  switch (mType) {
    case BuildingType::TownCenter:
      mSize = sf::Vector2f(2, 2);
      break;

    case BuildingType::Fort:
      mSize = sf::Vector2f(1, 1);
      break;

    case BuildingType::Stable:
      mSize = sf::Vector2f(2, 1);
      break;

    default:
      break;
  }
}

bool Building::addEntity(const Game& game, Player& player,
                         const EntityType& entT, entMap ressourceMap) {
  switch (mType) {
    case BuildingType::TownCenter:
      switch (entT) {
        case EntityType::Villager:
          return player.addEntity(game, entT, mPos + sf::Vector2f(mSize.x, 0),
                                  ressourceMap);
          break;

        default:
          std::cout << "Town cannot create this entity\n";
          return false;
          break;
      }
      break;

    case BuildingType::Fort:
      switch (entT) {
        case EntityType::Warrior:
          return player.addEntity(game, entT, mPos + sf::Vector2f(mSize.x, 0),
                                  ressourceMap);
          break;

        default:
          std::cout << "Fort cannot create this entity\n";
          return false;
          break;
      }
      break;

    default:
      return false;
      break;
  }
}

bool operator==(const Building& left, const Building& right) {
  return left.getID() == right.getID() && left.getColor() == right.getColor();
}
bool operator!=(const Building& left, const Building& right) {
  return !(left == right);
}
