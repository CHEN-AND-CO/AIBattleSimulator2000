#ifndef TYPE_HPP
#define TYPE_HPP

/*
Define the type of the buildings and entities used in the game
*/

#include <SFML/System.hpp>
<<<<<<< HEAD
#include <cmath>
#include <map>

enum class BuildingType { TownCenter, Fort, Stable,MaxBuildingType };
enum class EntityType { Villager, Warrior, Horse, MaxEntityType };
enum class Direction { Up, Down, Left, Right, MaxDirection };
enum class Ressource { Wood, Food, Gold, MaxRessources };
=======

enum class BuildingType { TownCenter, Fort, MaxBuildingType };
enum class EntityType { Villager, Warrior, MaxEntityType };
enum class Direction { Up, Down, Left, Right, MaxDirection };
enum class Ressource { Wood, MaxRessources };
>>>>>>> origin/advancedServerImplement

#define TILESIZE 16

bool rectCollide(const sf::Vector2f& pos1, const sf::Vector2f& size1,
                 const sf::Vector2f& pos2, const sf::Vector2f& size2);
bool rectCollide(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
<<<<<<< HEAD
bool rectInCircle(const sf::Vector2f pos1, int radius, sf::Vector2f pos2);

using buildMap = std::map<BuildingType, std::map<Ressource, int>>;
using entMap = std::map<EntityType, std::map<Ressource, int>>;
=======
>>>>>>> origin/advancedServerImplement

#endif
