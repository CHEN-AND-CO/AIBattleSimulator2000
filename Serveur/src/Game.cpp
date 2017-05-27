#include "Game.hpp"
#include <algorithm>
#include <iostream>

Game::Game() {
  std::map<Ressource, int> r;
  r[Ressource::Wood] = 600;
  r[Ressource::Gold] = 100;
  r[Ressource::Food] = 0;
  mBuildingCost[BuildingType::TownCenter] = r;

  r[Ressource::Wood] = 200;
  r[Ressource::Gold] = 50;
  r[Ressource::Food] = 0;
  mBuildingCost[BuildingType::Fort] = r;

  r[Ressource::Wood] = 300;
  r[Ressource::Gold] = 100;
  r[Ressource::Food] = 0;
  mBuildingCost[BuildingType::Stable] = r;

  r[Ressource::Wood] = 0;
  r[Ressource::Gold] = 0;
  r[Ressource::Food] = 50;
  mEntityCost[EntityType::Villager] = r;

  r[Ressource::Wood] = 0;
  r[Ressource::Gold] = 10;
  r[Ressource::Food] = 60;
  mEntityCost[EntityType::Warrior] = r;

  r[Ressource::Wood] = 10;
  r[Ressource::Gold] = 20;
  r[Ressource::Food] = 100;
  mEntityCost[EntityType::Horse] = r;
}

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

<<<<<<< HEAD
std::vector<std::vector<int>> Game::getVisibleMap(const sf::Color& col) const {
  auto output = mMap;
  std::vector<std::vector<int>> cache;
  for (const auto& play : mPlayer) {
    if (play.getColor() == col) {
      cache = play.getCache();
      break;
    }
  }
  for (unsigned x{0}; x < mMap.size(); x++) {
    for (unsigned y{0}; y < mMap.size(); y++) {
      if (cache[y][x] == 0) {
        output[y][x] = 0;
      }
    }
  }
  return output;
}

std::vector<Building> Game::getVisibleBuildings(const sf::Color& col) const {
  std::vector<std::vector<int>> cache;
  for (const auto& play : mPlayer) {
    if (play.getColor() == col) {
      cache = play.getCache();
      break;
    }
  }

  std::vector<Building> output;

  for (const auto& build : getBuildings()) {
    if (cache[build.getPosition().y][build.getPosition().x]) {
      output.push_back(build);
    }
  }

  return output;
}

std::vector<Entity> Game::getVisibleEntities(const sf::Color& col) const {
  std::vector<std::vector<int>> cache;
  for (const auto& play : mPlayer) {
    if (play.getColor() == col) {
      cache = play.getCache();
      break;
    }
  }

  std::vector<Entity> output;

  for (const auto& ent : getEntities()) {
    if (cache[ent.getPosition().y][ent.getPosition().x]) {
      output.push_back(ent);
    }
  }

  return output;
}
=======
bool Game::isGameFinish() const { return mPlayer.size() == 1; }
>>>>>>> origin/advancedServerImplement

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
<<<<<<< HEAD
  return Player(*this, sf::Color::Black, sf::Vector2f(0, 0), mBuildingCost,
                mEntityCost, 0);
=======
  return Player(sf::Color::Black, sf::Vector2f(0, 0));
>>>>>>> origin/advancedServerImplement
}

std::vector<Building> Game::getBuildings(const sf::Color& col) const {
  for (unsigned i{0}; i < mPlayer.size(); i++) {
    if (mPlayer[i].getColor() == col) {
      return mPlayer[i].getBuildings();
    }
  }
  return std::vector<Building>();
}

std::vector<Entity> Game::getEntities(const sf::Color& col) const {
  for (unsigned i{0}; i < mPlayer.size(); i++) {
    if (mPlayer[i].getColor() == col) {
      return mPlayer[i].getEntities();
    }
  }
  return std::vector<Entity>();
}

void Game::clearPlayer() {
  std::vector<int> indexs;
  for (unsigned i{0}; i < mPlayer.size(); i++) {
    mPlayer[i].clearMaps();
    if (mPlayer[i].getBuildings().size() == 0 &&
        mPlayer[i].getEntities().size() == 0) {
      indexs.push_back(i);
    }
  }
  for (auto i : indexs) {
    mPlayer.erase(mPlayer.begin() + i);
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

<<<<<<< HEAD
bool Game::attack(const sf::Color& col, int index, const Direction& dir) {
=======
bool Game::attack(const sf::Color& col, int index) {
>>>>>>> origin/advancedServerImplement
  for (auto& player1 : mPlayer) {
    sf::Color pCol = player1.getColor();
    if (pCol != col) {
      continue;
    }

    for (auto& player2 : mPlayer) {
      if (pCol == player2.getColor()) {
        continue;
      }

<<<<<<< HEAD
      sf::Vector2f pos = player1.getEntities()[index].getPosition();
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

      for (unsigned i{0}; i < player2.getEntities().size(); i++) {
        if (rectCollide(pos, player2.getEntities()[i].getPosition())) {
          player2.receiveDamageEntity(player1.getEntities()[index].getDamage(),
                                      i);
          return true;
        } else if (rectCollide(pos, player2.getEntities()[i].getPosition())) {
          player2.receiveDamageEntity(player1.getEntities()[index].getDamage(),
                                      i);
          return true;
        } else if (rectCollide(pos, player2.getEntities()[i].getPosition())) {
          player2.receiveDamageEntity(player1.getEntities()[index].getDamage(),
                                      i);
          return true;
        } else if (rectCollide(pos, player2.getEntities()[i].getPosition())) {
=======
      for (unsigned i{0}; i < player2.getEntities().size(); i++) {
        if (rectCollide(
                player1.getEntities()[index].getPosition() + sf::Vector2f(1, 0),
                player2.getEntities()[i].getPosition())) {
          player2.receiveDamageEntity(player1.getEntities()[index].getDamage(),
                                      i);
          return true;
        } else if (rectCollide(player1.getEntities()[index].getPosition() +
                                   sf::Vector2f(-1, 0),
                               player2.getEntities()[i].getPosition())) {
          player2.receiveDamageEntity(player1.getEntities()[index].getDamage(),
                                      i);
          return true;
        } else if (rectCollide(player1.getEntities()[index].getPosition() +
                                   sf::Vector2f(0, 1),
                               player2.getEntities()[i].getPosition())) {
          player2.receiveDamageEntity(player1.getEntities()[index].getDamage(),
                                      i);
          return true;
        } else if (rectCollide(player1.getEntities()[index].getPosition() +
                                   sf::Vector2f(0, -1),
                               player2.getEntities()[i].getPosition())) {
>>>>>>> origin/advancedServerImplement
          player2.receiveDamageEntity(player1.getEntities()[index].getDamage(),
                                      i);
          return true;
        }
      }

      for (unsigned i{0}; i < player2.getBuildings().size(); i++) {
        if (rectCollide(
                player1.getEntities()[index].getPosition() + sf::Vector2f(1, 0),
                sf::Vector2f(1, 1), player2.getBuildings()[i].getPosition(),
                player2.getBuildings()[i].getSize())) {
          player2.receiveDamageBuilding(
              player1.getEntities()[index].getDamage(), i);
          return true;
        } else if (rectCollide(player1.getEntities()[index].getPosition() +
                                   sf::Vector2f(-1, 0),
                               sf::Vector2f(1, 1),
                               player2.getBuildings()[i].getPosition(),
                               player2.getBuildings()[i].getSize())) {
          player2.receiveDamageBuilding(
              player1.getEntities()[index].getDamage(), i);
          return true;
        } else if (rectCollide(player1.getEntities()[index].getPosition() +
                                   sf::Vector2f(0, 1),
                               sf::Vector2f(1, 1),
                               player2.getBuildings()[i].getPosition(),
                               player2.getBuildings()[i].getSize())) {
          player2.receiveDamageBuilding(
              player1.getEntities()[index].getDamage(), i);
          return true;
        } else if (rectCollide(player1.getEntities()[index].getPosition() +
                                   sf::Vector2f(0, -1),
                               sf::Vector2f(1, 1),
                               player2.getBuildings()[i].getPosition(),
                               player2.getBuildings()[i].getSize())) {
          player2.receiveDamageBuilding(
              player1.getEntities()[index].getDamage(), i);
          return true;
        }
      }
    }
  }
  return false;
}
