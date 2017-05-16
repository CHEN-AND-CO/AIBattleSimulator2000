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

    case BuildingType::MaxBuildingType:
    default:
      break;
  }
}

void Building::addEntity(Player& player, const EntityType& entT) {
  switch (mType) {
    case BuildingType::TownCenter:
      switch (entT) {
        case EntityType::Villager:
          player.addEntity(entT, mPos + sf::Vector2f(mSize.x, 0));
          break;

        default:
          std::cout << "Town cannot create this entity\n";
      }
      break;

    case BuildingType::Fort:
      switch (entT) {
        case EntityType::Warrior:
          player.addEntity(entT, mPos + sf::Vector2f(mSize.x, 0));
          break;

        default:
          std::cout << "Fort cannot create this entity\n";
      }
      break;

    default:
      break;
  }
}
