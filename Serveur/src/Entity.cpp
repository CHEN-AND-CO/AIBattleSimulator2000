#include "Entity.hpp"
#include "Building.hpp"
#include "Game.hpp"

void Entity::addBuilding(Game& game, const BuildingType& type) {
  game.addBuilding(type, mColor, mPos);
}
