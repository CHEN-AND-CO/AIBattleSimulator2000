#include "Game.hpp"
#include <algorithm>
#include <iostream>

bool Game::loadFile(const std::string& fileName) {
  std::ifstream file(fileName, std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error open file " << fileName << std::endl;
    return false;
  }
  int n, tmp;
  file >> n;
  for (int i{0}; i < n; i++) {
    mMap.push_back(std::vector<int>(n));
    for (int j{0}; j < n; j++) {
      file >> tmp;
      mMap[i][j] = tmp;
    }
  }
  return true;
}

bool Game::isGameFinish() const { return mPlayer.size() == 1; }

sf::Color Game::getWinner() const {
  if (isGameFinish()) {
    return mPlayer[0].getColor();
  }
  return sf::Color::Black;
}

std::vector<Building> Game::getBuildings() const {
  std::vector<Building> v, build;
  for (const auto& player : mPlayer) {
    build = player.getBuildings();
    for (const auto& b : build) {
      v.push_back(b);
    }
  }
  return v;
}

std::vector<Entity> Game::getEntities() const {
  std::vector<Entity> v, ent;
  for (const auto& player : mPlayer) {
    ent = player.getEntities();
    for (const auto& b : ent) {
      v.push_back(b);
    }
  }
  return v;
}

Player Game::getPlayer(const sf::Color& col) const {
  for (unsigned i{0}; i < mPlayer.size(); i++) {
    if (mPlayer[i].getColor() == col) {
      return mPlayer[i];
    }
  }
}

std::vector<Building> Game::getBuildings(const sf::Color& col) const {
  for (unsigned i{0}; i < mPlayer.size(); i++) {
    if (mPlayer[i].getColor() == col) {
      return mPlayer[i].getBuildings();
    }
  }
}

std::vector<Entity> Game::getEntities(const sf::Color& col) const {
  for (unsigned i{0}; i < mPlayer.size(); i++) {
    if (mPlayer[i].getColor() == col) {
      return mPlayer[i].getEntities();
    }
  }
}

bool Game::moveEntity(const Direction& dir, const sf::Color& col, int i) {
  for (auto& player : mPlayer) {
    if (player.getColor() == col) {
      // Verification des limites de la map
      auto entToMove = player.getEntities()[i];
      sf::Vector2f pos = entToMove.getPosition();
      if (dir == Direction::Up && pos.y <= 0) {
        return false;
      } else if (dir == Direction::Left && pos.x <= 0) {
        return false;
      } else if (dir == Direction::Down && pos.y >= mMap.size() - 1) {
        return false;
      } else if (dir == Direction::Right && pos.x >= mMap[0].size() - 1) {
        return false;
      }
      // Verification de collision avec entites
      for (const auto& ent : getEntities()) {
        if (ent != entToMove) {
          Entity e = entToMove;
          e.move(dir, *this);
          if (rectCollide(ent.getPosition(), e.getPosition())) {
            return false;
          }
        }
      }
      // Verification de collision avec building
      for (const auto& build : getBuildings()) {
        Entity e = entToMove;
        e.move(dir, *this);
        if (rectCollide(build.getPosition(), build.getSize(), e.getPosition(),
                        sf::Vector2f(1, 1))) {
          return false;
        }
      }
      return player.moveEntity(dir, *this, i);
    }
  }
  return false;
}

bool Game::putRessourcesInTown(const Direction& dir, const sf::Color& col,
                               int index) {
  for (auto& p : mPlayer) {
    if (p.getColor() == col) {
      sf::Vector2f pos = p.getEntities()[index].getPosition();
      switch (dir) {
        case Direction::Up:
          pos.y--;
          break;

        case Direction::Down:
          pos.y++;
          break;

        case Direction::Left:
          pos.x--;
          break;

        case Direction::Right:
          pos.x++;
          break;

        default:
          break;
      }
      for (auto& b : p.getBuildings()) {
        if (b.getType() == BuildingType::TownCenter) {
          if (rectCollide(pos, sf::Vector2f(1, 1), b.getPosition(),
                          b.getSize())) {
            return p.putRessourcesInTown(index);
          }
        }
      }
    }
  }
  return false;
}

bool Game::attack(const sf::Color& col, int index) {
  for (auto& player : mPlayer) {
    sf::Color pCol = player.getColor();
    if (pCol != col) {
      return false;
    }
    for (auto& ent : getEntities()) {
      if (pCol != ent.getColor()) {
        if (rectCollide(
                player.getEntities()[index].getPosition() + sf::Vector2f(1, 0),
                ent.getPosition())) {
          ent.receiveDamage(player.getEntities()[index].getDamage());
          std::cout<<ent.getHealth()<<std::endl;
          return true;
        } else if (rectCollide(player.getEntities()[index].getPosition() +
                                   sf::Vector2f(-1, 0),
                               ent.getPosition())) {
          ent.receiveDamage(player.getEntities()[index].getDamage());
          std::cout<<ent.getHealth()<<std::endl;
          return true;
        } else if (rectCollide(player.getEntities()[index].getPosition() +
                                   sf::Vector2f(0, 1),
                               ent.getPosition())) {
          ent.receiveDamage(player.getEntities()[index].getDamage());
          std::cout<<ent.getHealth()<<std::endl;
          return true;
        } else if (rectCollide(player.getEntities()[index].getPosition() +
                                   sf::Vector2f(0, -1),
                               ent.getPosition())) {
          ent.receiveDamage(player.getEntities()[index].getDamage());
          std::cout<<ent.getHealth()<<std::endl;
          return true;
        }
      }
    }
    for (auto& build : getBuildings()) {
      if (pCol != build.getColor()) {
        if (rectCollide(
                player.getEntities()[index].getPosition() + sf::Vector2f(1, 0),
                sf::Vector2f(1, 1), build.getPosition(), build.getSize())) {
          build.receiveDamage(player.getEntities()[index].getDamage());
          return true;
        } else if (rectCollide(player.getEntities()[index].getPosition() +
                                   sf::Vector2f(-1, 0),
                               sf::Vector2f(1, 1), build.getPosition(),
                               build.getSize())) {
          build.receiveDamage(player.getEntities()[index].getDamage());
          return true;
        } else if (rectCollide(player.getEntities()[index].getPosition() +
                                   sf::Vector2f(0, 1),
                               sf::Vector2f(1, 1), build.getPosition(),
                               build.getSize())) {
          build.receiveDamage(player.getEntities()[index].getDamage());
          return true;
        } else if (rectCollide(player.getEntities()[index].getPosition() +
                                   sf::Vector2f(0, -1),
                               sf::Vector2f(1, 1), build.getPosition(),
                               build.getSize())) {
          build.receiveDamage(player.getEntities()[index].getDamage());
          return true;
        }
      }
    }
  }
  return false;
}
