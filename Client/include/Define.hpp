#ifndef TYPE_HPP
#define TYPE_HPP

/*
Define the type of the buildings and entities used in the game
*/

#include <SFML/System.hpp>
#include <cmath>

enum class BuildingType { TownCenter, Fort, MaxBuildingType };
enum class EntityType { Villager, Warrior, MaxEntityType };
enum class Direction { Up, Down, Left, Right, MaxDirection };
enum class Ressource { Wood, MaxRessources };

#define GROUND 1
#define TREE 2
#define WATER 3

#define TILESIZE 16
#define FORT_PRICE 200
#define TOWNCENTER_PRICE 600
#define VILLAGER_PRICE 50
#define WARRIOR_PRICE 60

#define MAX_RESSOURCES 20
#define DELAY 500
#define QUIT_FIRST_STATE 5

bool rectCollide(const sf::Vector2f& pos1, const sf::Vector2f& size1,
                 const sf::Vector2f& pos2, const sf::Vector2f& size2);
bool rectCollide(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
bool rectInCircle(const sf::Vector2f pos1, int radius, sf::Vector2f pos2);

#endif
