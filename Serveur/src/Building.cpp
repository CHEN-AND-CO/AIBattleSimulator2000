#include "Building.hpp"
#include "Entity.hpp"
#include "Game.hpp"

void Building::addEntity(Game& game, const EntityType& entT) {
  game.addEntity(entT, mColor, mPos);
}
