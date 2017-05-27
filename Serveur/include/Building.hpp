#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <SFML/Graphics.hpp>
#include "Define.hpp"

class Entity;

class Game;

class Player;

class Building {
 public:
  Building(BuildingType bT, sf::Color color, sf::Vector2f pos, int id);

  bool addEntity(const Game& game, Player& player, const EntityType& entT, entMap ressourceMap);

  BuildingType getType() const { return mType; }
  sf::Color getColor() const { return mColor; }
  sf::Vector2f getPosition() const { return mPos; }
  sf::Vector2f getSize() const { return mSize; }
  int getID() const { return mID; }
  int getHealth() const { return mHealth; }

  void receiveDamage(int damage) { mHealth -= damage; };
  bool isAlive() { return mHealth > 0; }

 private:
  BuildingType mType;
  sf::Color mColor;
  sf::Vector2f mPos;
  sf::Vector2f mSize;
  int mHealth;
  int mID;
};

bool operator==(const Building& left, const Building& right);
bool operator!=(const Building& left, const Building& right);

#endif
