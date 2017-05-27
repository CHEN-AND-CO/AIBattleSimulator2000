#include "IA.hpp"

/***********************/
/*Fonctions à supprimer*/
/***********************/
void IA::pause(unsigned time) {
  for (unsigned i{0}; i < time * 10000000; i++) {
    std::cout << "";
  }
}

void IA::printTile(Tile tile){
	std::cout << "Tile : " << tile.position.x << "/" << tile.position.y << " _ " << tile.strength << std::endl;
}

void IA::printInfos(Game& game){
	sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        break;
        
      default:
      	break;
    }
  }
  
	int wood = game.getPlayer(mColor).getRessources(Ressource::Wood);
	int villagers = 0;
	int warriors = 0;
	
	for(const auto& entity : game.getPlayer(mColor).getEntities()){
		if(entity.getType() == EntityType::Villager){
			villagers++;
		} else if(entity.getType() == EntityType::Warrior){
			warriors++;
		}
	}
	
	std::string infos = int2Str(townCenter) + " centre(s) ville et " + int2Str(fort) + " fort(s).\n";
	infos += int2Str(villagers) + " villageois et " + int2Str(warriors) + " combatant(s).\n";
	infos += int2Str(wood) + " bois.";
	
	sf::Font font;
	sf::Text text;
	
	font.loadFromFile("ressources/arial.ttf");

	text.setFont(font);
	text.setString(infos);
	text.setCharacterSize(15);
	text.setPosition(sf::Vector2f(1, 1));
	
	sf::RectangleShape r(sf::Vector2f(window.getSize().x, window.getSize().y));
  r.setFillColor(mColor);
  r.setPosition(0, 0);

	window.clear();

  window.draw(r);
	window.draw(text);
	
	window.display();
}
