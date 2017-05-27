#include "IA.hpp"

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
        if (isTileFree(game, aroundPoint[j])) {
          /*Si c'est du sol on l'ajoute au tableau de case de la map*/
          aroundMap.push_back(aroundPoint[j]);
        }
      } else if (game.getMap()[aroundPoint[j].y][aroundPoint[j].x] == TREE) {
        /*Si c'est un arbre*/
        if (isAroundFree(game, aroundPoint[j], index)) {
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
        if (isTileFree(game, aroundPoint[j])) {
          /*Si c'est du sol on l'ajoute au tableau de case de la map*/
          aroundMap.push_back(aroundPoint[j]);
        }
        /*S'il est en collision avec le town center, on est arrivé*/
        if (rectCollide(aroundPoint[j], sf::Vector2f(1, 1), town, townSize)) {
          if (isAroundFree(game, aroundPoint[j], index)) {
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

sf::Vector2f IA::findFortPosition(Game& game, const sf::Vector2f pos, int index) {
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
  
  sf::Vector2f marge = sf::Vector2f(4, 2);
  
  town.x = town.x-marge.x;
  town.y = town.y-marge.y;
  townSize.x = townSize.x+marge.x/2;
  townSize.y = townSize.y+marge.y*2;

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
        if (isTileFree(game, aroundPoint[j])) {
          /*Si c'est du sol on l'ajoute au tableau de case de la map*/
          aroundMap.push_back(aroundPoint[j]);
        }
        /*S'il est en collision avec le town center, on est arrivé*/
        if (rectCollide(aroundPoint[j], sf::Vector2f(1, 1), town, townSize)) {
          if (isAroundFree(game, aroundPoint[j], index)) {
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

  /*Retour de la dernière position du tableau, celle du fort*/
  if (finded) {
    return aroundMap[aroundMap.size() - 1];
  } else {
    return sf::Vector2f(-1, -1);
  }
}

sf::Vector2f IA::computePosition(Game& game, const sf::Vector2f pos, int index) {
  sf::Vector2f next = pos;
  
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> disy(1, 39);
  std::uniform_int_distribution<> disx(1, 39);
  
  next.x = disx(gen);
	next.y = disy(gen);
	
  return next;
}

sf::Vector2f IA::computeWarriorPosition(Game& game, const sf::Vector2f pos, int index) {
  sf::Vector2f next = pos;
  
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> disy(1, 39);
  std::uniform_int_distribution<> disx(1, 39);
  
  do{
		next.x = disx(gen);
		next.y = disy(gen);
	}while(manhattan(pos, next) > 18 || manhattan(pos, next) < 16 || !isFree(game, next, index));

  return next;
}

sf::Vector2f IA::computeWarriorPositionEnnemi(Game& game, const sf::Vector2f pos, int index) {
  sf::Vector2f top = pos;
  sf::Vector2f right = pos;
  sf::Vector2f bot = pos;
  sf::Vector2f left = pos;
  sf::Vector2f next = sf::Vector2f(45, 45);
  sf::Vector2f player = game.getPlayer(mColor).getEntities()[index].getPosition();

  top.y--;
  right.x++;
  bot.y++;
  left.x--;

	if(isFree(game, top, index)){
		next = top;
	}
	if(isFree(game, right, index)){
		next = (manhattan(next, player) < manhattan(right, player))?top:right;
	}
	if(isFree(game, bot, index)){
		next = (manhattan(next, player) < manhattan(bot, player))?next:bot;
	}
	if(isFree(game, left, index)){
		next = (manhattan(next, player) < manhattan(left, player))?next:left;
	}

  if(next == sf::Vector2f(45, 45)){
  	next = sf::Vector2f(-1, -1);
  }

  return next;
}

sf::Vector2f IA::search(Game& game, const sf::Vector2f pos, int index) {
	/*Déclaration des variables*/
  std::vector<sf::Vector2f> aroundMap;
  std::vector<sf::Vector2f> aroundPoint;
  bool finded = false;
  unsigned size{0};
  unsigned sizeMax{15};

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
      	if(isEnnemyBuilding(game, aroundPoint[j])) {
      		/*S'il n'y a pas de joueurs autour de la case on l'ajoute*/
          aroundMap.push_back(aroundPoint[j]);
          finded = true;
          /*C'est la fin du chemin*/
          aroundMap.push_back(aroundMap[i]);
          break;
      	} else if(isEnnemy(game, aroundPoint[j])){
        	/*S'il n'y a pas de joueurs autour de la case on l'ajoute*/
          aroundMap.push_back(aroundPoint[j]);
          finded = true;
          /*C'est la fin du chemin*/
          aroundMap.push_back(aroundMap[i]);
          break;
        } else if (isFree(game, aroundPoint[j], index)) {
          /*Si c'est du sol on l'ajoute au tableau de case de la map*/
          aroundMap.push_back(aroundPoint[j]);
        }
      }
    }
    /*Vidage du tableau de points autour de la case*/
    aroundPoint.clear();
    
    if(size >= sizeMax){
    	break;
    }
    
    size++;
  }
  
  /*Retour de la dernière position du tableau, celle de l'arbre*/
  if (finded) {
    mEntities[index].position = aroundMap[aroundMap.size() - 1];
    return aroundMap[aroundMap.size() - 1];
  } else {
    mEntities[index].position = sf::Vector2f(-1, -1);
    return sf::Vector2f(-1, -1);
  }
}

sf::Vector2f IA::searchEnnemi(Game& game, const sf::Vector2f pos, int index) {
	/*Déclaration des variables*/
  bool finded = false;
  unsigned sizeMax{10};
  
  if(!posInMap(game, pos)){
  	return sf::Vector2f(-1, -1);
  }

  for (const auto& player : game.getPlayer()) {
  	for(const auto& entity : player.getEntities()){
		  if(entity.getColor() != mColor || entity.getPosition() != pos){
	  		finded = rectInCircle(pos, sizeMax, entity.getPosition());
	  		
	  		if(finded){
	  			mEntities[index].position = entity.getPosition();
	  			return entity.getPosition();
	  		}
		  }
    }
  }
  
  /*Retour de la dernière position du tableau, celle de l'arbre*/
  mEntities[index].position = sf::Vector2f(-1, -1);
  return sf::Vector2f(-1, -1);
}

sf::Vector2f IA::findEnnemiBuilding(Game& game, const sf::Vector2f pos, int index) {
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
        if (isTileFree(game, aroundPoint[j])) {
          /*Si c'est du sol on l'ajoute au tableau de case de la map*/
          aroundMap.push_back(aroundPoint[j]);
        }
        /*S'il est en collision avec le town center, on est arrivé*/
        if (rectCollide(aroundPoint[j], sf::Vector2f(1, 1), town, townSize)) {
          if (isAroundFree(game, aroundPoint[j], index)) {
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
