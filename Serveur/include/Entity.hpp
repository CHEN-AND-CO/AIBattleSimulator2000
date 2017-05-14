#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Define.hpp"

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

  void move(Direction dir, Game& game);
  void receiveDamage(int damage) { mHealth =- damage; };
  bool isAlive() { return mHealth > 0; }

 private:
  EntityType mType;
  sf::Color mColor;
  sf::Vector2f mPos;
  int mHealth;
};

#endif
