#include "Building.hpp"
#include "Game.hpp"

void Building::addEntity(Game& game, const EntityType& entT) {
  game.addEntity(entT, mColor, mPos);
}
