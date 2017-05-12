#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Type.hpp"

class Building;

class Game;

/*
Define an entity which can interact with the world
Can Construct building, collect ressources and attack
*/

class Entity {
 public:
  Entity(const EntityType& entT, sf::Color col, sf::Vector2f pos)
      : mType{entT}, mColor{col}, mPos{pos}, mHealth{100} {}

  void addBuilding(Game& game, const BuildingType& buildT);

  EntityType getType() const { return mType; }
  sf::Color getColor() const { return mColor; }
  sf::Vector2f getPosition() const { return mPos; }

 private:
  EntityType mType;
  sf::Color mColor;
  sf::Vector2f mPos;
  int mHealth;
};

#endif
