#include "IA.hpp"
#include <iostream>

IA::IA(Game *game, sf::Color color){
  mColor = color;
  mGame = game;
  
  delay = sf::milliseconds(DELAY);
  
  unsigned i;
  
  for(i = 0; i < mGame->getPlayer(mColor).getEntities().size(); i++){
    action.push_back(0);
    state.push_back(0);
    count.push_back(0);
  }
}

void IA::run(){
  if(clock.getElapsedTime() < delay){
    return;
  }
  clock.restart();
  unsigned i;
  
  for(i = 0; i < mGame->getPlayer(mColor).getEntities().size(); i++){
    switch(state[i]){
      case 0:
        switch(action[i]){
          case 0:
            std::cout << i << ":Chercher arbre" << std::endl;
            count[i]=toForest(i);
            
            if(count[i]){
              count[i] = 0;
              action[i] = 1;
            }
            break;
            
          case 1:
            std::cout << i << ":Collecter" << std::endl;
            collect(i);
            count[i]++;
            
            if(mGame->getPlayer(mColor).getTransportedRessources(i) >= MAX_RESSOURCES || count[i] >= MAX_RESSOURCES+1){
              count[i] = 0;
              action[i] = 2;
              std::cout << i << ":Ressources transportées : " << mGame->getPlayer(mColor).getTransportedRessources(i) << std::endl;
            }
            break;
            
          case 2:
            std::cout << i << ":Rentrer" << std::endl;
            count[i]=toHome(i);
            
            if(count[i]){
              count[i] = 0;
              action[i] = 3;
            }
            break;
            
          case 3:
            std::cout << i << ":Ranger" << std::endl;
            store(i);
            
            if(mGame->getPlayer(mColor).getRessources(Ressource::Wood) <= VILLAGER_PRICE){
              count[i] = 0;
              action[i] = 0;
              std::cout << i << ":Ressources entreposées : " << mGame->getPlayer(mColor).getRessources(Ressource::Wood) << std::endl;
            } else {
              count[i] = 0;
              action[i] = 4;
            }
            break;
            
          case 4:
            std::cout << i << ":Créer villageois" << std::endl;
            mGame->addEntity(EntityType::Villager, mColor, 0);
            action.push_back(0);
            state.push_back(0);
            count.push_back(0);
            
            std::cout << i << ":Ressources entreposées : " << mGame->getPlayer(mColor).getRessources(Ressource::Wood) << std::endl;
            std::cout << i << ":Villageois : " << mGame->getPlayer(mColor).getEntities().size() << std::endl;
            
            if(mGame->getPlayer(mColor).getEntities().size() >= QUIT_FIRST_STATE){
              state[i] = 1;
            }
            
            action[i] = 0;
            count[i] = 0;
            
            break;
          
          default:
            break;
        }
        break;
      
      default:
        break;
    }
  }
}

bool IA::collect(int index){
  return mGame->collectRessource(Direction::Up, mColor, index)
      || mGame->collectRessource(Direction::Down, mColor, index)
      || mGame->collectRessource(Direction::Left, mColor, index)
      || mGame->collectRessource(Direction::Right, mColor, index);
}

bool IA::store(int index){
  return mGame->putRessourcesInTown(Direction::Up, mColor, index)
      || mGame->putRessourcesInTown(Direction::Down, mColor, index)
      || mGame->putRessourcesInTown(Direction::Left, mColor, index)
      || mGame->putRessourcesInTown(Direction::Right, mColor, index);
}
  
int IA::toForest(int index){
  return 0;
}

int IA::toHome(int index){
  return 0;
}
