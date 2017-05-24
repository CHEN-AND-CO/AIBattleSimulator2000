#include "IA.hpp"

IA::IA(Game& game, sf::Color color) : mColor{color} {
	delay = sf::milliseconds(DELAY);
  
  window.create(sf::VideoMode(250, 150), "Données " + std::to_string(mColor.r)+" "+std::to_string(mColor.g)+" "+std::to_string(mColor.b));

  for (unsigned i{0}; i < game.getPlayer(mColor).getEntities().size(); i++) {
    mEntities.push_back({0, 0, Work::Woodcutter, sf::Vector2f(-1, -1), true});
  }
  
  villagerLimit = QUIT_FIRST_STATE + 1;
  warriorLimit = 1000;
  stopWarriors = false;
  start = computeWarriorPosition(game, game.getBuildings(mColor)[0].getPosition(), -1);
  
  test = 0;
  verify = false;
}

/****************************/
/*Lancement et arrêt de l'IA*/
/****************************/

void IA::run(Game& game) {
	if(verify){
		test = 1;
	} else {
		test = 0;
	}
	
  if (clock.getElapsedTime() < delay) {
    return;
  }
  clock.restart();
  
  townCenter = 0;
  fort = 0;
  wood = game.getPlayer(mColor).getRessources(Ressource::Wood);
	
	unsigned i{0};
	unsigned nbWarrior{0};
  
  for(const auto& entity : game.getPlayer(mColor).getEntities()){
  	if(entity.getType() == EntityType::Warrior){
  		nbWarrior++;
  	}
  }
  
  if(nbWarrior >= warriorLimit){
  	start = sf::Vector2f(20, 20);
  	stopWarriors = true;
  }
  
  for (const auto& building : game.getBuildings(mColor)) {
    if (building.getType() == BuildingType::TownCenter) {
      townCenter++;
    } else if (building.getType() == BuildingType::Fort) {
     	fort++;
    }
  }
  
  if(fort > 0 && townCenter > 0 && wood >= /*TOWNCENTER_PRICE + FORT_PRICE + VILLAGER_PRICE*8 + */WARRIOR_PRICE && !stopWarriors){
  	if(game.addEntity(EntityType::Warrior, mColor, 1)){
		  mEntities.push_back({0, 0, Work::Waiter, sf::Vector2f(-1, -1), true});
		}
  } else if(townCenter < 0){
    
	} else if(game.getPlayer(mColor).getEntities().size() < villagerLimit
		 && wood >= VILLAGER_PRICE){
    if(game.addEntity(EntityType::Villager, mColor, 0)){
		  mEntities.push_back({0, 0, Work::Woodcutter, sf::Vector2f(-1, -1), true});
		}
	}
  
  printInfos(game);
  
  i = 0;
	
  for (const auto& entity : game.getPlayer(mColor).getEntities()) {
  	if(game.getPlayer(mColor).getEntities()[i].getType() == EntityType::Warrior){
  		if(mEntities[i].state != Work::Warrior && mEntities[i].action != 2){
	  		if(search(game, game.getPlayer(mColor).getEntities()[i].getPosition(), i) != sf::Vector2f(-1, -1)){
	  			changeState(Work::Warrior, i);
	  		}
  		}
  	}
  	
  	switch (mEntities[i].state) {
      case Work::Woodcutter:
        switch (mEntities[i].action) {
          case 0:
          	if(entity.getType() == EntityType::Villager){
		          mEntities[i].count = toForest(game, i);

		          if (mEntities[i].count) {
		            changeAction(1, i);
		          }
            }
            break;

          case 1:
          	if(entity.getType() == EntityType::Villager){
		          collect(game, i);
		          mEntities[i].count++;

		          if (game.getPlayer(mColor).getTransportedRessources(i) >=
		                  MAX_TRANSPORTED_RESSOURCES ||
		              mEntities[i].count >= MAX_TRANSPORTED_RESSOURCES + 5) {
		            changeAction(2, i);
		          }
            }
            break;

          case 2:
          	if(entity.getType() == EntityType::Villager){
		        	mEntities[i].count = toHome(game, i);
		        	if(!townCenter){
		        		changeState(Work::Explorer, i);
		        	}

		          if (mEntities[i].count) {
		            changeAction(3, i);
		          }
            }
            break;

          case 3:
          	if(entity.getType() == EntityType::Villager){
		        	store(game, i);

		          if (wood <=
		              VILLAGER_PRICE) {
		            changeAction(0, i);
		          } else {
		            changeAction(4, i);
		          }
            }
            break;

          case 4:
          	if(entity.getType() == EntityType::Villager){
							if (i >= QUIT_FIRST_STATE && fort < 1) {
		              changeState(Work::Architect, i);
		          }

		          changeAction(0, i);
						}
            break;

          default:
            break;
        }
        break;

      case Work::Explorer:
      	switch (mEntities[i].action) {
          case 0:
          	if(entity.getType() == EntityType::Villager){
		          mEntities[i].count = explore(game, i);
		      
						  if(mEntities[i].count){
						  	changeState(Work::Waiter, i);
						  }
				    } else if(entity.getType() == EntityType::Warrior){
      				mEntities[i].count = explore(game, i);
		      
						  if(mEntities[i].count){
						  	changeState(Work::Waiter, i);
						  	changeAction(1, i);
						  }
      			}
            break;

          default:
            break;
        }
        break;

      case Work::Architect:
      	switch (mEntities[i].action) {
          case 0:
          	if(entity.getType() == EntityType::Villager){
		          mEntities[i].count = explore(game, i);
		      
						  if(mEntities[i].count){
						  	changeAction(1, i);
						  }
				    }
            break;
            
          case 1:
          	if(entity.getType() == EntityType::Villager){
		          mEntities[i].count = toFortPosition(game, i);
		      
						  if(mEntities[i].count){
						  	changeAction(2, i);
						  }
				    }
            break;
            
          case 2:
          	if(entity.getType() == EntityType::Villager){
		          mEntities[i].count = construct(game, BuildingType::Fort, i);
		      
						  if(mEntities[i].count){
						  	changeState(Work::Woodcutter, i);
						  }
				    }
            break;

          default:
            break;
        }
        break;

      case Work::Waiter:
      	switch (mEntities[i].action) {
          case 0:
          	if(entity.getType() == EntityType::Villager){
      	
				  	} else if(entity.getType() == EntityType::Warrior){
				  		//mEntities[i].count = align(game, i);
				  		mEntities[i].count++;
				  		
				  		if(mEntities[i].count >= 10){
				  			changeState(Work::Explorer, i);
				  		}
				  	}
            break;
            
          case 1:
          	if(entity.getType() == EntityType::Villager){
      	
				  	} else if(entity.getType() == EntityType::Warrior){
				  	
				  	}
            break;
            
          case 2:
          	if(entity.getType() == EntityType::Villager){
      	
				  	} else if(entity.getType() == EntityType::Warrior){
				  	
				  	}
            break;

          default:
            break;
        }
        break;

      case Work::Warrior:
      	switch (mEntities[i].action) {
          case 0:
          	if(entity.getType() == EntityType::Villager){
      				
				  	} else if(entity.getType() == EntityType::Warrior){
				  		if(search(game, game.getPlayer(mColor).getEntities()[i].getPosition(), i) == sf::Vector2f(-1, -1)){
				  			changeAction(1, i);
				  			break;
				  		}
				  		
			  			mEntities[i].count = goTo(game, mEntities[i].position, i);
			  			
			  			if(mEntities[i].count){
								changeAction(1, i);
							}
				  	}
            break;
            
          case 1:
          	if(entity.getType() == EntityType::Villager){
      				
				  	} else if(entity.getType() == EntityType::Warrior){
				  		//game.attack(mColor, i);
				  		changeState(Work::Explorer, i);
				  	}
            break;

          default:
            break;
        }
        break;

      default:
        break;
    }
    
    i++;
  }
}

/***************************/
/*Déplacements des entitées*/
/***************************/
int IA::toForest(Game& game, int index) {
  if (mEntities[index].position.x == -1 && mEntities[index].position.y == -1) {
    mEntities[index].position = findFreeTree(game,
        game.getPlayer(mColor).getEntities()[index].getPosition(), index);
  }
  if (mEntities[index].position.x != -1 && mEntities[index].position.y != -1){
  	if(!isAroundFree(game, mEntities[index].position, index)){
  		mEntities[index].position = findFreeTree(game,
        	game.getPlayer(mColor).getEntities()[index].getPosition(), index);
  	}
  }

  return goTo(game, mEntities[index].position, index);
}

int IA::toHome(Game& game, int index) {
  if (mEntities[index].position.x == -1 && mEntities[index].position.y == -1) {
    mEntities[index].position = findTown(game, 
        game.getPlayer(mColor).getEntities()[index].getPosition(), index);
  }
  if (mEntities[index].position.x != -1 && mEntities[index].position.y != -1){
  	if(!isAroundFree(game, mEntities[index].position, index)){
  		mEntities[index].position = findTown(game,
        	game.getPlayer(mColor).getEntities()[index].getPosition(), index);
  	}
  }

  return goTo(game, mEntities[index].position, index);
}

int IA::toFortPosition(Game& game, int index) {
  if (mEntities[index].position.x == -1 && mEntities[index].position.y == -1) {
    mEntities[index].position = findFortPosition(game, 
        game.getPlayer(mColor).getEntities()[index].getPosition(), index);
  }
  if (mEntities[index].position.x != -1 && mEntities[index].position.y != -1){
  	if(!isAroundFree(game, mEntities[index].position, index)){
  		mEntities[index].position = findFortPosition(game,
        	game.getPlayer(mColor).getEntities()[index].getPosition(), index);
  	}
  }

  return goTo(game, mEntities[index].position, index);
}

int IA::explore(Game& game, int index) {
  if (mEntities[index].position.x == -1 && mEntities[index].position.y == -1) {
    mEntities[index].position = computePosition(game, 
        game.getPlayer(mColor).getEntities()[index].getPosition(), index);
  }
  if (mEntities[index].position.x != -1 && mEntities[index].position.y != -1){
  	if(!isAroundFree(game, mEntities[index].position, index)){
  		mEntities[index].position = computePosition(game,
        	game.getPlayer(mColor).getEntities()[index].getPosition(), index);
  	}
  }
  
  return goTo(game, mEntities[index].position, index);
}

int IA::align(Game& game, int index) {
	sf::Vector2f left = start + sf::Vector2f(-1, 1);
	sf::Vector2f right = start - sf::Vector2f(-1, 1);
	sf::Vector2f plus = minManhattan(start + sf::Vector2f(1, 1), start + sf::Vector2f(-1, 1), game.getBuildings(mColor)[0].getPosition());
	plus = minManhattan(start + sf::Vector2f(1, 1), start + sf::Vector2f(1, -1), game.getBuildings(mColor)[0].getPosition());
	plus = minManhattan(start + sf::Vector2f(1, 1), start + sf::Vector2f(-1, -1), game.getBuildings(mColor)[0].getPosition());
	plus = minManhattan(start + sf::Vector2f(-1, 1), start + sf::Vector2f(1, -1), game.getBuildings(mColor)[0].getPosition());
	plus = minManhattan(start + sf::Vector2f(-1, 1), start + sf::Vector2f(-1, -1), game.getBuildings(mColor)[0].getPosition());
	plus = minManhattan(start + sf::Vector2f(1, -1), start + sf::Vector2f(-1, -1), game.getBuildings(mColor)[0].getPosition());
	
	plus -= start;
	
	while(mEntities[index].position.x == -1 && mEntities[index].position.y == -1){
		if(isFree(game, start, index)){
			mEntities[index].position = start;
		} else if(isFree(game, left, index)){
			mEntities[index].position = left;
		} else if(isFree(game, right, index)){
			mEntities[index].position = right;
		} else {
			if(isGround(game, left + sf::Vector2f(-1, 1))){
				left += sf::Vector2f(-1, 1);
			} else if(isGround(game, right - sf::Vector2f(-1, 1))){
				right -= sf::Vector2f(-1, 1);
			} else {
				start += plus;
				left = start + sf::Vector2f(-1, 1);
				right = start - sf::Vector2f(-1, 1);
			}
		}
	}
  
  return goTo(game, mEntities[index].position, index);
}

bool IA::goTo(Game& game, const sf::Vector2f pos, int index) {
  sf::Vector2f player =
      game.getPlayer(mColor).getEntities()[index].getPosition();
  sf::Vector2f next;

  if (pos == player) {
    return true;
  }
  
  next = pathfinder(game, pos, index);
  
  if(next == sf::Vector2f(-2, -2) || next == sf::Vector2f(-1, -1)){
  	mEntities[index].position = sf::Vector2f(-1, -1);
  }

  move(game, next, index);
  
  if(verify){
		next = pathfinder(game, pos, index);
  }

  return false;
}

/*******************/
/*Fonctions tierces*/
/*******************/

void IA::changeState(Work work, int index){
	changeAction(0, index);
  mEntities[index].state = work;
}

void IA::changeAction(int act, int index){
	mEntities[index].count = 0;
  mEntities[index].action = act;
  mEntities[index].position.x = -1;
  mEntities[index].position.y = -1;
}

std::string IA::int2Str(int x)
{
	std::stringstream type;
	type << x;
	return type.str();
}

template<typename T> std::vector<T> remove(std::vector<T> vect, int index){
	std::vector<T> result;
	
	for(unsigned i{0}; i < vect.size(); i++){
		if((signed)i == index){
			continue;
		}
		result.push_back(vect[i]);
	}
	
	return result;
}
