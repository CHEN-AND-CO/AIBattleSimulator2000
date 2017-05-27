#ifndef DEFINE_HPP
#define DEFINE_HPP

#include <iostream>
#include <string>
#include <utility>

/*
Define the type of the buildings and entities used in the game
*/

enum class BuildingType { TownCenter, Fort, MaxBuildingType };
enum class EntityType { Villager, Warrior, MaxEntityType };
enum class Direction { Up, Down, Left, Right, MaxDirection };
enum class Ressource { Wood, MaxRessources };

std::pair<std::string, std::pair<unsigned, std::string>> getData(
    const std::string& input);

#endif
