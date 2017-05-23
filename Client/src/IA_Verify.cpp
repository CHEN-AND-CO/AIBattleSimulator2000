#include "IA.hpp"

/****************************/
/*Vérifications de positions*/
/****************************/
bool IA::isTileFree(Game& game, const sf::Vector2f pos) {
  std::vector<sf::Vector2f> point;

  if(!posInMap(game, pos)){
  	return false;
  }

  point.push_back(pos);

  for (const auto& player : game.getPlayer(mColor).getEntities()) {
    if (pointExist(player.getPosition(), point)) {
      return false;
    }
  }

  return true;
}

bool IA::isAroundFree(Game& game, const sf::Vector2f pos, unsigned index) {
  std::vector<sf::Vector2f> aroundPoints;
  unsigned i = 0;

  if(!posInMap(game, pos)){
  	return false;
  }

  computePoints(game, pos, aroundPoints);

  for (const auto& player : game.getPlayer(mColor).getEntities()) {
    if (pointExist(player.getPosition(), aroundPoints) && i != index) {
    	return false;
    }
    i++;
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

bool IA::pointExist(Tile firstTile,
                    std::vector<Tile> aroundMap) {
  for (const auto& tile : aroundMap) {
    if (tile.position == firstTile.position && tile.strength >= firstTile.strength) {
      return true;
    }
  }

  return false;
}

bool IA::isPlayer(Game& game, const sf::Vector2f pos, int index) {
  std::vector<sf::Vector2f> point;
  sf::Vector2f posPlayer = game.getPlayer(mColor).getEntities()[index].getPosition();
  
  if(!posInMap(game, pos)){
  	return false;
  }

  point.push_back(pos);

  for (const auto& player : game.getPlayer()) {
  	for(const auto& entity : player.getEntities()){
		  if (pointExist(entity.getPosition(), point)) {
		  	if(entity.getColor() != mColor || entity.getPosition() != posPlayer){
		  		return true;
		  	}
		  }
    }
  }

  return false;
}

bool IA::isBuilding(Game& game, const sf::Vector2f pos) {
  if(!posInMap(game, pos)){
  	return false;
  }

  for (const auto& building : game.getBuildings()) {
    if (rectCollide(building.getPosition(), building.getSize(),
                 pos, sf::Vector2f(1, 1))) {
      return true;
    }
  }

  return false;
}

bool IA::isFree(Game& game, const sf::Vector2f pos, int index) {
	if(!posInMap(game, pos)){
  	return false;
  }

  if(game.getMap()[pos.y][pos.x] != GROUND){
		return false;
	}
	
  std::vector<sf::Vector2f> point;
  sf::Vector2f posPlayer = game.getPlayer(mColor).getEntities()[index].getPosition();

  point.push_back(pos);

  for (const auto& player : game.getPlayer()) {
  	for(const auto& entity : player.getEntities()){
		  if (pointExist(entity.getPosition(), point)) {
		  	if(entity.getColor() != mColor || entity.getPosition() != posPlayer){
		  		return false;
		  	}
		  }
    }
  }

  for (const auto& building : game.getBuildings()) {
    if (rectCollide(building.getPosition(), building.getSize(),
                 pos, sf::Vector2f(1, 1))) {
      return false;
    }
  }

  return true;
}

bool IA::isGround(Game& game, const sf::Vector2f pos) {
	if(!posInMap(game, pos)){
  	return false;
  }

  if(game.getMap()[pos.y][pos.x] != GROUND){
		return false;
	}

  return true;
}

bool IA::isEnnemy(Game& game, const sf::Vector2f pos) {
  std::vector<sf::Vector2f> point;

  if(!posInMap(game, pos)){
  	return false;
  }

  point.push_back(pos);

  for (const auto& player : game.getPlayer()) {
  	for(const auto& entity : player.getEntities()){
		  if (pointExist(entity.getPosition(), point) && entity.getColor() != mColor) {
		  	return true;
		  }
    }
  }

  return false;
}
