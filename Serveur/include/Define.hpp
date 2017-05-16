#ifndef TYPE_HPP
#define TYPE_HPP

/*
Define the type of the buildings and entities used in the game
*/

#include <SFML/System.hpp>

enum class BuildingType { TownCenter, Fort, MaxBuildingType };
enum class EntityType { Villager, Warrior, MaxEntityType };
enum class Direction { Up, Down, Left, Right, MaxDirection };
enum class Ressource { Wood, MaxRessources };

#define TILESIZE 16

bool rectCollide(const sf::Vector2f& pos1, const sf::Vector2f& size1,
                 const sf::Vector2f& pos2, const sf::Vector2f& size2);
bool rectCollide(const sf::Vector2f& pos1, const sf::Vector2f& pos2);

#endif
