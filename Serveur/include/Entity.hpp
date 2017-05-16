#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Define.hpp"

class Building;

class Game;

class Player;

/*
Define an entity which can interact with the world
Can Construct building, collect ressources and attack
*/

class Entity {
 public:
  Entity(const EntityType& entT, sf::Color col, sf::Vector2f pos, int id);

  void addBuilding(Player& player, const BuildingType& buildT);

  EntityType getType() const { return mType; }
  sf::Color getColor() const { return mColor; }
  sf::Vector2f getPosition() const { return mPos; }
  int getID() const { return mID; }
  int getHealth() const { return mHealth; }
  int getDamage() { return mDamage; }

  bool move(Direction dir, const Game& game);
  void receiveDamage(int damage) {
    //std::cout << damage << std::endl;
    //std::cout << mHealth << std::endl;
    mHealth -= damage;
    //std::cout << mHealth << std::endl;
  }
  bool isAlive() { return mHealth > 0; }

  bool collectRessource(const Game& game, const Player& p, Direction dir);
  bool putRessourcesInTown(Player& player);

 private:
  EntityType mType;
  sf::Color mColor;
  sf::Vector2f mPos;
  int mHealth;
  int mID;
  Ressource currentRessource;
  int currentTransportedRessources;
  int mDamage;
};

bool operator==(const Entity& left, const Entity& right);
bool operator!=(const Entity& left, const Entity& right);

#endif
