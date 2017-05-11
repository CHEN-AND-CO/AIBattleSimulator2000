#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Type.hpp"

class Building;

class Game;

class Entity {
 public:
  Entity(const EntityType& entT, sf::Color col, sf::Vector2f pos)
      : mType{entT}, mColor{col}, mPos{pos} {}

  void addBuilding(Game& game, const BuildingType& type);

  EntityType getType() { return mType; }
  sf::Color getColor() { return mColor; }
  sf::Vector2f getPosition() { return mPos; }

 private:
  EntityType mType;
  sf::Color mColor;
  sf::Vector2f mPos;
};

#endif
