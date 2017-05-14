#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <SFML/Graphics.hpp>
#include "Type.hpp"

class Entity;

class Game;

class Building {
 public:
  Building(BuildingType bT, sf::Color color, sf::Vector2f pos)
      : mType{bT}, mColor{color}, mPos{pos}, mHealth{1000} {
    switch (mType) {
      case BuildingType::Town:
        mSize = sf::Vector2f(2*32, 2*32);
        break;

      case BuildingType::MaxBuildingType:
      default:
        break;
    }
  }

  void addEntity(Game& game, const EntityType& entT);

  BuildingType getType() const { return mType; }
  sf::Color getColor() const { return mColor; }
  sf::Vector2f getPosition() const { return mPos; }
  sf::Vector2f getSize() const { return mSize; }

  void receiveDamage(int damage) { mHealth = -damage; };
  bool isAlive() { return mHealth > 0; }

 private:
  BuildingType mType;
  sf::Color mColor;
  sf::Vector2f mPos;
  sf::Vector2f mSize;
  int mHealth;
};

#endif
