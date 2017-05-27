#include "IA.hpp"

sf::Vector2f IA::pathfinder(Game& game, const sf::Vector2f pos, int index){
	/*Déclaration des variables*/
  std::vector<Tile> aroundMap;
  std::vector<Tile> aroundPoint;
  std::vector<Tile> liste;
  bool finded = false;
	Tile temp;
	sf::Vector2f player = game.getPlayer(mColor).getEntities()[index].getPosition();
	
	if(player == pos){
		return player;
	}
	
	temp.position = player;
	temp.parent = NULL;
	temp.strength = manhattan(player, pos);
	
	aroundMap.push_back(temp);

  for (unsigned i{0}; i < aroundMap.size() && !finded; i++) {
    computePoints(game, aroundMap[i].position, aroundPoint, aroundMap[i], pos);

    for (unsigned j{0}; j < aroundPoint.size(); j++) {
      if (pointExist(aroundPoint[j], aroundMap)) {
        continue;
      }

      if (game.getMap()[aroundPoint[j].position.y][aroundPoint[j].position.x] == GROUND
      		&& !isPlayer(game, aroundPoint[j].position, index)
      		&& !isBuilding(game, aroundPoint[j].position)) {
        aroundMap.push_back(aroundPoint[j]);
      }
      if (aroundPoint[j].position == pos){
      	if(!isPlayer(game, aroundPoint[j].position, index)
      			&& !isBuilding(game, aroundPoint[j].position)) {
		      aroundMap.push_back(aroundPoint[j]);
		      finded = true;
		      break;
        } else {
        	return sf::Vector2f(-2, -2);
        }
      }
    }
    aroundPoint.clear();
  }
 	
 	liste.push_back(aroundMap[aroundMap.size() - 1]);
 	while(liste[liste.size()-1].position != player){
 		liste.push_back(*liste[liste.size() - 1].parent);
 	}
	
	/*Retour de la dernière position du tableau, celle du center*/
  if (finded && liste.size()) {
  	if(liste.size() == 1){
  		return liste[liste.size()-1].position;
  	} else {
    	return liste[liste.size()-2].position;
    }
  } else {
    return sf::Vector2f(-1, -1);
  }
  
}
