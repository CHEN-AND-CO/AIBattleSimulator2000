#include "IA.hpp"

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
	if(pos.x < 0 && pos.y < 0){
		return;
	}
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

bool IA::construct(Game& game, BuildingType type, int index) {
 	if(game.getPlayer(mColor).getRessources(Ressource::Wood) >= FORT_PRICE){
		game.addBuilding(type, mColor, index);
		if(game.getPlayer(mColor).getRessources(Ressource::Wood) < FORT_PRICE){
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
