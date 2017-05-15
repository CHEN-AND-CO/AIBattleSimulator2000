#include "Entity.hpp"
#include <iostream>
#include "Building.hpp"
#include "Game.hpp"

/*
Function which create a building if this entity can create it
depending of the types of both of them
*/

void Entity::addBuilding(Game& game, const BuildingType& buildT) {
  switch (mType) {
    case EntityType::Villager:
      switch (buildT) {
        case BuildingType::Fort:
          game.addBuilding(buildT, mColor, mPos);
          break;

        default:
          std::cout << "Villager cannot construct this Building\n";
      }
      break;

    case EntityType::Warrior:
      switch (buildT) {
        default:
          std::cout << "Warrior cannot construct this building\n";
      }
      break;

    default:
      break;
  }
}

// Deplacemant d'une unite
void Entity::move(Direction dir, const Game& game) {
  // Mouvement en Haut
  if (dir == Direction::Up) {
    int futurePos = game.getMap()[mPos.y - 1][mPos.x];
    if (futurePos == 1) {  // Verifie si la position est valide (terrain)
      mPos.y--;
    }

    // Mouvement en bas
  } else if (dir == Direction::Down) {
    int futurePos = game.getMap()[mPos.y + 1][mPos.x];
    if (futurePos == 1) {  // Verifie si la position est valide (terrain)
      mPos.y++;
    }

    // Mouvement a gauche
  } else if (dir == Direction::Left) {
    int futurePos = game.getMap()[mPos.y][mPos.x - 1];
    if (futurePos == 1) {  // Verifie si la position est valide (terrain)
      mPos.x--;
    }

    // Mouvement a droite
  } else if (dir == Direction::Right) {
    int futurePos = game.getMap()[mPos.y][mPos.x + 1];
    if (futurePos == 1) {  // Verifie si la position est valide (terrain)
      mPos.x++;
    }
  }
}

bool operator==(const Entity& left, const Entity& right) {
  return left.getID() == right.getID();
}
bool operator!=(const Entity& left, const Entity& right) {
  return !(left == right);
}
