#include "Building.hpp"
#include <iostream>
#include "Entity.hpp"
#include "Game.hpp"

/*
Function which create an entity if this building can create it
depending of the types of both of them
*/
void Building::addEntity(Game& game, const EntityType& entT) {
  switch (mType) {
    case BuildingType::Town:
      switch (entT) {
        case EntityType::Villager:
          game.addEntity(entT, mColor, mPos);
          break;

        default:
          std::cout << "Town cannot create this entity\n";
      }
      break;

    case BuildingType::Fort:
      switch (entT) {
        case EntityType::Warrior:
          game.addEntity(entT, mColor, mPos);
          break;

        default:
          std::cout << "Fort cannot create this entity\n";
      }
      break;

    default:
      break;
  }
}
