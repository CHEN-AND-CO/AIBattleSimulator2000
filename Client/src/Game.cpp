#include "Game.hpp"

Game::Game(const sf::IpAddress& ip, unsigned short port, std::string name)
    : mClient(name) {
  mClient.connect(ip, port);
}

std::vector<std::vector<int>> Game::getMap() {
  std::string data;
  std::vector<std::vector<int>> output;

  mClient.send(mClient.getName() + "@getEntitysMap:0");

  while ((data = mClient.receive()) == "Error") {
  }

  auto datas = getData(data);

  if (datas.first != "terrain") {
    std::cout << "Wrong command received" << std::endl;
    return output;
  }

  unsigned n = std::sqrt(datas.second.first);

  data = datas.second.second;

  for (unsigned i{0}; i < n; i++) {
    output.push_back(std::vector<int>(n));
    for (unsigned j{0}; j < n; j++) {
      output[i][j] = std::stoi(data.substr(0, 1));
      data = data.substr(data.find(' ', 1) + 1);
    }
  }

  return output;
}

std::vector<Building> Game::getBuildings() {
  std::string data;
  std::vector<Building> output;

  mClient.send(mClient.getName() + "@getTerrainMap:0");

  while ((data = mClient.receive()) == "Error") {
  }

  auto datas = getData(data);

  if (datas.first != "buildings") {
    std::cout << "Wrong command received" << std::endl;
    return output;
  }

  data = datas.second.second;

  for (unsigned i{0}; i < datas.second.first / 7; i++) {
    Building build;

    // get position
    build.mPositon.x = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);
    build.mPositon.y = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);

    // get color
    build.mColor.r = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);
    build.mColor.g = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);
    build.mColor.b = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);

    // get hp
    build.hp = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);

    // get type
    auto pos = data.find(' ');
    if (pos == std::string::npos) {
      if (data == "TypeCenter") {
        build.mType = BuildingType::TownCenter;
      } else if (data == "Fort") {
        build.mType = BuildingType::Fort;
      }
    } else {
      if (data.substr(0, data.find(' ')) == "TypeCenter") {
        build.mType = BuildingType::TownCenter;
      } else if (data.substr(0, data.find(' ')) == "Fort") {
        build.mType = BuildingType::Fort;
      }
      data = data.substr(data.find(' ') + 1);
    }

    output.push_back(build);
  }

  return output;
}

std::vector<Entity> Game::getEntities() {
  std::string data;
  std::vector<Entity> output;

  mClient.send(mClient.getName() + "@getEntityMap:0");

  while ((data = mClient.receive()) == "Error") {
  }

  auto datas = getData(data);

  if (datas.first != "entitys") {
    std::cout << "Wrong command received" << std::endl;
    return output;
  }

  data = datas.second.second;

  for (unsigned i{0}; i < datas.second.first / 7; i++) {
    Entity ent;

    // get position
    ent.mPositon.x = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);
    ent.mPositon.y = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);

    // get color
    ent.mColor.r = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);
    ent.mColor.g = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);
    ent.mColor.b = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);

    // get hp
    ent.hp = std::stoi(data.substr(0, data.find(' ')));
    data = data.substr(data.find(' ') + 1);

    // get tyoe
    auto pos = data.find(' ');
    if (pos == std::string::npos) {
      if (data == "Villager") {
        ent.mType = EntityType::Villager;
      } else if (data == "Warrior") {
        ent.mType = EntityType::Warrior;
      }
    } else {
      if (data.substr(0, data.find(' ')) == "Villager") {
        ent.mType = EntityType::Villager;
      } else if (data.substr(0, data.find(' ')) == "Warrior") {
        ent.mType = EntityType::Warrior;
      }
      data = data.substr(data.find(' ') + 1);
    }

    output.push_back(ent);
  }

  return output;
}

std::vector<Building> Game::getBuildings(const sf::Color& color) {
  auto build = getBuildings();
  std::vector<Building> output;

  for (const auto& b : build) {
    if (b.mColor == color) {
      output.push_back(b);
    }
  }
  return output;
}
std::vector<Entity> Game::getEntities(const sf::Color& color) {
  auto ent = getEntities();
  std::vector<Entity> output;

  for (const auto& e : ent) {
    if (e.mColor == color) {
      output.push_back(e);
    }
  }
  return output;
}

bool Game::attack(const Direction& dir, const sf::Color& col, int index) {
  std::string data = mClient.getName() + "@attack:5 " + std::to_string(col.r) +
                     " " + std::to_string(col.g) + " " + std::to_string(col.b) +
                     " " + std::to_string(index) + " ";
  switch (dir) {
    case Direction::Up:
      data += "up";
      break;

    case Direction::Down:
      data += "down";
      break;

    case Direction::Left:
      data += "left";
      break;

    case Direction::Right:
      data += "right";
      break;

    default:
      break;
  }

  mClient.send(data);

  while ((data = mClient.receive()) == "Error") {
  }

  auto datas = getData(data);

  if (datas.first != "reply") {
    std::cout << "Wrong command received" << std::endl;
    return false;
  }

  return datas.second.second == "ok";
}

bool Game::moveEntity(const Direction& dir, const sf::Color& col, int index) {
  std::string data = mClient.getName() + "@move:5 " + std::to_string(col.r) +
                     " " + std::to_string(col.g) + " " + std::to_string(col.b) +
                     " " + std::to_string(index) + " ";
  switch (dir) {
    case Direction::Up:
      data += "up";
      break;

    case Direction::Down:
      data += "down";
      break;

    case Direction::Left:
      data += "left";
      break;

    case Direction::Right:
      data += "right";
      break;

    default:
      break;
  }

  mClient.send(data);

  while ((data = mClient.receive()) == "Error") {
  }

  auto datas = getData(data);

  if (datas.first != "reply") {
    std::cout << "Wrong command received" << std::endl;
    return false;
  }

  return datas.second.second == "ok";
}

bool Game::collectRessource(const Direction& dir, const sf::Color& col,
                            int index) {
  std::string data = mClient.getName() + "@collect:5 " + std::to_string(col.r) +
                     " " + std::to_string(col.g) + " " + std::to_string(col.b) +
                     " " + std::to_string(index) + " ";
  switch (dir) {
    case Direction::Up:
      data += "up";
      break;

    case Direction::Down:
      data += "down";
      break;

    case Direction::Left:
      data += "left";
      break;

    case Direction::Right:
      data += "right";
      break;

    default:
      break;
  }

  mClient.send(data);

  while ((data = mClient.receive()) == "Error") {
  }

  auto datas = getData(data);

  if (datas.first != "reply") {
    std::cout << "Wrong command received" << std::endl;
    return false;
  }

  return datas.second.second == "ok";
}

bool Game::putRessourcesInTown(const Direction& dir, const sf::Color& col,
                               int index) {
  std::string data = mClient.getName() + "@putintown:5 " +
                     std::to_string(col.r) + " " + std::to_string(col.g) + " " +
                     std::to_string(col.b) + " " + std::to_string(index) + " ";
  switch (dir) {
    case Direction::Up:
      data += "up";
      break;

    case Direction::Down:
      data += "down";
      break;

    case Direction::Left:
      data += "left";
      break;

    case Direction::Right:
      data += "right";
      break;

    default:
      break;
  }

  mClient.send(data);

  while ((data = mClient.receive()) == "Error") {
  }

  auto datas = getData(data);

  if (datas.first != "reply") {
    std::cout << "Wrong command received" << std::endl;
    return false;
  }

  return datas.second.second == "ok";
}
