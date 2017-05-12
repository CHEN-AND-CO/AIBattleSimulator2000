#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <SFML/Graphics.hpp>
#include "Type.hpp"

class Entity;

class Game;

class Building {
 public:
  Building(BuildingType bT, sf::Color color, sf::Vector2f pos)
      : mType{bT}, mColor{color}, mPos{pos} {
    switch (mType) {
      case BuildingType::Town:
        mSize = sf::Vector2f(3, 3);
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

 private:
  BuildingType mType;
  sf::Color mColor;
  sf::Vector2f mPos;
  sf::Vector2f mSize;
};

#endif
