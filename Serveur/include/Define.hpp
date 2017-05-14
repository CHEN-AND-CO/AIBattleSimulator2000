#ifndef TYPE_HPP
#define TYPE_HPP

/*
Define the type of the buildings and entities used in the game
*/

enum class BuildingType { Town, Fort, MaxBuildingType };
enum class EntityType { Villager, Warrior, MaxEntityType };
enum class Direction { Up, Down, Left, Right, MaxDirection };

#define TILESIZE 32

#endif
