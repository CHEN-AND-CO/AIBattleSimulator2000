#include "Entity.hpp"
#include <iostream>
#include "Building.hpp"
#include "Game.hpp"
#include "Player.hpp"

/*
Function which create a building if this entity can create it
depending of the types of both of them
*/

Entity::Entity(const EntityType& entT, sf::Color col, sf::Vector2f pos, int id)
    : mType{entT}, mColor{col}, mPos{pos}, mHealth{100}, mID{id} {
  switch (mType) {
    case EntityType::Villager:
      mDamage = 5;
      break;
    case EntityType::Warrior:
      mDamage = 60;
      break;
    default:
      break;
  }
}

void Entity::addBuilding(Player& player, const BuildingType& buildT) {
  if (mType != EntityType::Villager) {
    std::cout << "This entity cannot construct buildings\n";
    return;
  }
  player.addBuilding(buildT, mPos + sf::Vector2f(1, 0));
}

// Deplacemant d'une unite
bool Entity::move(Direction dir, const Game& game) {
  // Mouvement en Haut
  if (dir == Direction::Up) {
    int futurePos = game.getMap()[mPos.y - 1][mPos.x];
    if (futurePos == 1) {  // Verifie si la position est valide (terrain)
      mPos.y--;
      return true;
    }

    // Mouvement en bas
  } else if (dir == Direction::Down) {
    int futurePos = game.getMap()[mPos.y + 1][mPos.x];
    if (futurePos == 1) {  // Verifie si la position est valide (terrain)
      mPos.y++;
      return true;
    }

    // Mouvement a gauche
  } else if (dir == Direction::Left) {
    int futurePos = game.getMap()[mPos.y][mPos.x - 1];
    if (futurePos == 1) {  // Verifie si la position est valide (terrain)
      mPos.x--;
      return true;
    }

    // Mouvement a droite
  } else if (dir == Direction::Right) {
    int futurePos = game.getMap()[mPos.y][mPos.x + 1];
    if (futurePos == 1) {  // Verifie si la position est valide (terrain)
      mPos.x++;
      return true;
    }
  }
  return false;
}

bool Entity::collectRessource(const Game& game, const Player& p,
                              Direction dir) {
  if (mType != EntityType::Villager) {
    std::cout << "This entity cannot collect Ressources\n";
    return false;
  }
  int caseValue;
  switch (dir) {
    case Direction::Up:
      caseValue = game.getMap()[mPos.y - 1][mPos.x];
      break;
    case Direction::Down:
      caseValue = game.getMap()[mPos.y + 1][mPos.x];
      break;
    case Direction::Left:
      caseValue = game.getMap()[mPos.y][mPos.x - 1];
      break;
    case Direction::Right:
      caseValue = game.getMap()[mPos.y][mPos.x + 1];
      break;
    default:
      break;
  }
  switch (caseValue) {
    case 2:
      if (currentRessource != Ressource::Wood) {
        currentRessource = Ressource::Wood;
        currentTransportedRessources = 0;
        break;
      }
      if (currentTransportedRessources >= 100) {
        return false;
      }
      currentTransportedRessources++;
      return true;
      break;

    default:
      break;
  }
  return false;
}

bool Entity::putRessourcesInTown(Player& player) {
  if (currentTransportedRessources != 0) {
    player.addRessource(currentRessource, currentTransportedRessources);
    currentTransportedRessources = 0;
    return true;
  }
  return false;
}

bool operator==(const Entity& left, const Entity& right) {
  return left.getID() == right.getID() && left.getColor() == right.getColor();
}
bool operator!=(const Entity& left, const Entity& right) {
  return !(left == right);
}
