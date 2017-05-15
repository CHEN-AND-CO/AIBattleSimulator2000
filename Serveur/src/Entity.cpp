#include "Entity.hpp"
#include <iostream>
#include "Building.hpp"
#include "Game.hpp"
#include "Player.hpp"

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
      currentTransportedRessources++;
      std::cout << "ent : " << currentTransportedRessources << std::endl;
      return true;
      break;

    default:
      return false;
      break;
  }
}

bool Entity::putRessourcesInTown(Player& player) {
  if (currentTransportedRessources != 0) {
    std::cout << "h\n";
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
