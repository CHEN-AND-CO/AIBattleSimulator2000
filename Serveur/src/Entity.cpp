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

void Entity::move(Direction dir, Game& game){
  if(dir == Direction::Up){
    if(game.getMap()[mPos.x][mPos.y-1] != 3){
      mPos.y--;
    }
  }
  else if(dir == Direction::Down){
    if(game.getMap()[mPos.x][mPos.y+1] != 3){
      mPos.y++;
    }
  }
  else if(dir == Direction::Left){
    if(game.getMap()[mPos.x-1][mPos.y] != 3){
      mPos.x--;
    }
  }
  else if(dir == Direction::Right){
    if(game.getMap()[mPos.x+1][mPos.y] != 3){
      mPos.x--;
    }
  }
}
