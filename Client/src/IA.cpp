#include "IA.hpp"

IA::IA(Game& game, sf::Color color) : mColor{color} {
  //mGame = game;
  delay = sf::milliseconds(DELAY);

  for (unsigned i{0}; i < game.getPlayer(mColor).getEntities().size(); i++) {
    action.push_back(0);
    state.push_back(0);
    count.push_back(0);
    mPosition.push_back(sf::Vector2f(-1, -1));
  }
}

/****************************/
/*Lancement et arrêt de l'IA*/
/****************************/

void IA::close() {
  /*action.clear();
  state.clear();
  count.clear();
  mPosition.clear();

  for(unsigned i{0}; i < game.getPlayer(mColor).getEntities().size(); i++){
    action.push_back(0);
    state.push_back(0);
    count.push_back(0);
    mPosition.push_back(sf::Vector2f(-1,-1));
  }*/
}

void IA::run(Game& game) {
  if (clock.getElapsedTime() < delay) {
    return;
  }
  clock.restart();

  for (unsigned i{0}; i < game.getPlayer(mColor).getEntities().size(); i++) {
    switch (state[i]) {
      case 0:
        switch (action[i]) {
          case 0:
            count[i] = toForest(game, i);

            if (count[i]) {
              count[i] = 0;
              action[i] = 1;
              mPosition[i] = sf::Vector2f(-1, -1);
            }
            break;

          case 1:
            collect(game, i);
            count[i]++;

            if (game.getPlayer(mColor).getTransportedRessources(i) >=
                    MAX_RESSOURCES ||
                count[i] >= MAX_RESSOURCES + 5) {
              count[i] = 0;
              action[i] = 2;
              std::cout << i << " transporte "
                        << game.getPlayer(mColor).getTransportedRessources(i)
                        << "bois"
                        << std::endl;
            }
            break;

          case 2:
            count[i] = toHome(game, i);

            if (count[i]) {
              count[i] = 0;
              action[i] = 3;
              mPosition[i] = sf::Vector2f(-1, -1);
            }
            break;

          case 3:
            store(game, i);

            if (game.getPlayer(mColor).getRessources(Ressource::Wood) <=
                VILLAGER_PRICE) {
              count[i] = 0;
              action[i] = 0;
              std::cout << "Ressources entreposées : "
                        << game.getPlayer(mColor).getRessources(
                               Ressource::Wood)
                        << std::endl;
            } else {
              count[i] = 0;
              action[i] = 4;
            }
            break;

          case 4:
            game.addEntity(EntityType::Villager, mColor, 0);
            action.push_back(0);
            state.push_back(0);
            count.push_back(0);
            mPosition.push_back(sf::Vector2f(-1, -1));

            if (game.getPlayer(mColor).getEntities().size() >=
                QUIT_FIRST_STATE) {
              for (unsigned j{0};
                   j < game.getPlayer(mColor).getEntities().size(); j++) {
                state[j] = 1;
              }
            }

            action[i] = 0;
            count[i] = 0;

            break;

          default:
            break;
        }
        break;

      case 1:
        goTo(game, sf::Vector2f(15, 15), i);
        break;

      default:
        break;
    }
  }
}

/***********************************/
/*Utilisation des actions de player*/
/***********************************/
bool IA::collect(Game& game, int index) {
  return game.collectRessource(Direction::Up, mColor, index) ||
         game.collectRessource(Direction::Down, mColor, index) ||
         game.collectRessource(Direction::Left, mColor, index) ||
         game.collectRessource(Direction::Right, mColor, index);
}

bool IA::store(Game& game, int index) {
  return game.putRessourcesInTown(Direction::Up, mColor, index) ||
         game.putRessourcesInTown(Direction::Down, mColor, index) ||
         game.putRessourcesInTown(Direction::Left, mColor, index) ||
         game.putRessourcesInTown(Direction::Right, mColor, index);
}

void IA::move(Game& game, const sf::Vector2f pos, int index) {
  sf::Vector2f player =
      game.getPlayer(mColor).getEntities()[index].getPosition();

  if (pos.x > player.x) {
    game.moveEntity(Direction::Right, mColor, index);
  } else if (pos.x < player.x) {
    game.moveEntity(Direction::Left, mColor, index);
  } else if (pos.y > player.y) {
    game.moveEntity(Direction::Down, mColor, index);
  } else if (pos.y < player.y) {
    game.moveEntity(Direction::Up, mColor, index);
  }
}

/***************************/
/*Déplacements des entitées*/
/***************************/
int IA::toForest(Game& game, int index) {
  if (mPosition[index].x == -1 && mPosition[index].y == -1) {
    mPosition[index] = findFreeTree(game,
        game.getPlayer(mColor).getEntities()[index].getPosition(), index);
  }

  return goTo(game, mPosition[index], index);
}

int IA::toHome(Game& game, int index) {
  if (mPosition[index].x == -1 && mPosition[index].y == -1) {
    mPosition[index] = findTown(game, 
        game.getPlayer(mColor).getEntities()[index].getPosition(), index);
  }

  return goTo(game, mPosition[index], index);
}

bool IA::goTo(Game& game, const sf::Vector2f pos, int index) {
  sf::Vector2f player =
      game.getPlayer(mColor).getEntities()[index].getPosition();

  if (pos == player) {
    return true;
  }

  sf::Vector2f next = findNextTile(game, pos, index);

  move(game, next, index);

  return false;
}

/*****************************/
/*Trouver une case sur la map*/
/*****************************/
sf::Vector2f IA::findFreeTree(Game& game, const sf::Vector2f pos, int index) {
  /*Déclaration des variables*/
  std::vector<sf::Vector2f> aroundMap;
  std::vector<sf::Vector2f> aroundPoint;
  bool finded = false;

  /*Ajout de la première position dans le tableau de la map, celle du joueur*/
  aroundMap.push_back(pos);

  /*Boucle tant que i est inférieure au nombre de cases dans le tableau de la
   * map*/
  for (unsigned i{0}; i < aroundMap.size() && !finded; i++) {
    /*Récupération des cases autour de la position i dans le tableau
     * aroundPoint*/
    computePoints(game, aroundMap[i], aroundPoint);

    /*Boucle tant que j est inférieure au nombre de cases dans le tableau
     * aroundPoint*/
    for (unsigned j{0}; j < aroundPoint.size(); j++) {
      /*Si le point existe dans le tableau de la map, on ne l'ajoute pas*/
      if (pointExist(aroundPoint[j], aroundMap)) {
        continue;
      }

      /*Vérification de ce que contient cette case*/
      if (game.getMap()[aroundPoint[j].y][aroundPoint[j].x] == GROUND) {
        if (isFree(game, aroundPoint[j])) {
          /*Si c'est du sol on l'ajoute au tableau de case de la map*/
          aroundMap.push_back(aroundPoint[j]);
        }
      } else if (game.getMap()[aroundPoint[j].y][aroundPoint[j].x] == TREE) {
        /*Si c'est un arbre*/
        if (isTileFree(game, aroundPoint[j])) {
          /*S'il n'y a pas de joueurs autour de la case on l'ajoute*/
          aroundMap.push_back(aroundPoint[j]);
          finded = true;
          /*C'est la fin du chemin*/
          aroundMap.push_back(aroundMap[i]);
          break;
        }
      }
    }
    /*Vidage du tableau de points autour de la case*/
    aroundPoint.clear();
  }
  
  /*Retour de la dernière position du tableau, celle de l'arbre*/
  if (finded) {
    return aroundMap[aroundMap.size() - 1];
  } else {
    return sf::Vector2f(-1, -1);
  }
}

sf::Vector2f IA::findTown(Game& game, const sf::Vector2f pos, int index) {
  /*Déclaration des variables*/
  std::vector<sf::Vector2f> aroundMap;
  std::vector<sf::Vector2f> aroundPoint;
  bool finded = false;
  sf::Vector2f town;
  sf::Vector2f townSize;

  for (unsigned i{0}; i < game.getBuildings(mColor).size(); i++) {
    if (game.getBuildings(mColor)[i].getType() == BuildingType::TownCenter) {
      town = game.getBuildings(mColor)[i].getPosition();
      townSize = game.getBuildings(mColor)[i].getSize();
    }
  }

  /*Ajout de la première position dans le tableau de la map, celle du joueur*/
  aroundMap.push_back(pos);

  /*Boucle tant que i est inférieure au nombre de cases dans le tableau de la
   * map*/
  for (unsigned i{0}; i < aroundMap.size() && !finded; i++) {
    /*Récupération des cases autour de la position i dans le tableau
     * aroundPoint*/
    computePoints(game, aroundMap[i], aroundPoint);

    /*Boucle tant que j est inférieure au nombre de cases dans le tableau
     * aroundPoint*/
    for (unsigned j{0}; j < aroundPoint.size(); j++) {
      /*Si le point existe dans le tableau de la map, on ne l'ajoute pas*/
      if (pointExist(aroundPoint[j], aroundMap)) {
        continue;
      }

      /*Vérification de ce que contient cette case*/
      if (game.getMap()[aroundPoint[j].y][aroundPoint[j].x] == GROUND) {
        if (isFree(game, aroundPoint[j])) {
          /*Si c'est du sol on l'ajoute au tableau de case de la map*/
          aroundMap.push_back(aroundPoint[j]);
        }
        /*S'il est en collision avec le town center, on est arrivé*/
        if (rectCollide(aroundPoint[j], sf::Vector2f(1, 1), town, townSize)) {
          if (isTileFree(game, aroundPoint[j])) {
            /*S'il n'y a pas de joueurs autour de la case on l'ajoute*/
            aroundMap.push_back(aroundPoint[j]);
            finded = true;
            /*C'est la fin du chemin*/
            aroundMap.push_back(aroundMap[i]);
            break;
          }
        }
      }
    }
    /*Vidage du tableau de points autour de la case*/
    aroundPoint.clear();
  }

  /*Retour de la dernière position du tableau, celle du center*/
  if (finded) {
    return aroundMap[aroundMap.size() - 1];
  } else {
    return sf::Vector2f(-1, -1);
  }
}

/************************************************/
/*Trouver la prochane case lors d'un déplacement*/
/************************************************/
sf::Vector2f IA::findNextTile(Game& game, const sf::Vector2f pos, int index) {
  std::vector<sf::Vector2f> aroundPoint;
  sf::Vector2f player =
      game.getPlayer(mColor).getEntities()[index].getPosition();
  int distance = manhattan(player, pos);

  computePoints(game, player, aroundPoint);

  for (unsigned j{0}; j < aroundPoint.size(); j++) {
    if (manhattan(aroundPoint[j], pos) > distance) {
      continue;
    }

    if (game.getMap()[aroundPoint[j].y][aroundPoint[j].x] == GROUND) {
      if (isFree(game, aroundPoint[j]) && manhattan(aroundPoint[j], pos) < distance) {
        return aroundPoint[j];
      }
    }
  }

  for (unsigned j{0}; j < aroundPoint.size(); j++) {
    if (manhattan(aroundPoint[j], pos) > distance) {
      continue;
    }

    if (game.getMap()[aroundPoint[j].y][aroundPoint[j].x] == GROUND) {
      if (isFree(game, aroundPoint[j]) &&
          manhattan(aroundPoint[j], pos) == distance) {
        return aroundPoint[j];
      }
    }
  }
  return sf::Vector2f(-1, -1);
}

/**************************************/
/*Calculs des points autour de la case*/
/**************************************/
void IA::computePoints(Game& game, const sf::Vector2f pos,
                       std::vector<sf::Vector2f>& aroundPoints) {
  sf::Vector2f top = pos;
  sf::Vector2f right = pos;
  sf::Vector2f bot = pos;
  sf::Vector2f left = pos;

  top.y--;
  right.x++;
  bot.y++;
  left.x--;

  if (posInMap(game, top)) {
    aroundPoints.push_back(top);
  }
  if (posInMap(game, right)) {
    aroundPoints.push_back(right);
  }
  if (posInMap(game, bot)) {
    aroundPoints.push_back(bot);
  }
  if (posInMap(game, left)) {
    aroundPoints.push_back(left);
  }
}

/*********/
/*Calculs*/
/*********/
int IA::manhattan(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

int IA::manhattan(const sf::Vector2f pos1, const sf::Vector2f pos2) {
  return manhattan(pos1.x, pos1.y, pos2.x, pos2.y);
}

/****************************/
/*Vérifications de positions*/
/****************************/
bool IA::isFree(Game& game, const sf::Vector2f pos) {
  std::vector<sf::Vector2f> point;

  point.push_back(pos);

  for (const auto& player : game.getPlayer(mColor).getEntities()) {
    if (pointExist(player.getPosition(), point)) {
      return false;
    }
  }

  for (const auto& building : game.getBuildings(mColor)) {
    if (pointExist(building.getPosition(), point)) {
      return false;
    }
  }

  return true;
}

bool IA::isTileFree(Game& game, const sf::Vector2f pos) {
  std::vector<sf::Vector2f> aroundPoints;

  computePoints(game, pos, aroundPoints);

  for (const auto& player : game.getPlayer(mColor).getEntities()) {
    if (pointExist(player.getPosition(), aroundPoints)) {
      return false;
    }
  }

  aroundPoints.clear();
  aroundPoints.push_back(pos);

  for (const auto& building : game.getBuildings(mColor)) {
    if (pointExist(building.getPosition(), aroundPoints)) {
      return false;
    }
  }

  return true;
}

bool IA::posInMap(Game& game, const sf::Vector2f pos) {
  if (pos.y <= 0) {
    return false;
  } else if (pos.x <= 0) {
    return false;
  } else if (pos.y >= game.getMap().size() - 1) {
    return false;
  } else if (pos.x >= game.getMap()[0].size() - 1) {
    return false;
  }
  return true;
}

bool IA::pointExist(const sf::Vector2f pos,
                    std::vector<sf::Vector2f> aroundMap) {
  for (const auto& position : aroundMap) {
    if (position == pos) {
      return true;
    }
  }

  return false;
}

/*******************/
/*Pause à supprimer*/
/*******************/
void IA::pause(unsigned time) {
  for (unsigned i{0}; i < time * 10000000; i++) {
    std::cout << "";
  }
}
