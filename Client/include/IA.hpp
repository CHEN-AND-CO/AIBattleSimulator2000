  #ifndef IA_HPP
  #define IA_HPP

  #include <SFML/Graphics.hpp>
  #include <SFML/Audio.hpp>
  #include <SFML/System.hpp>
  #include <cmath>
  #include <fstream>
  #include <iostream>
  #include <memory>
  #include <string>
  #include <vector>
  #include <random>
  #include <sstream>
  #include "Game.hpp"

	#define GROUND 1
	#define TREE 2
	#define WATER 3

	#define TILESIZE 16
	#define FORT_PRICE 200
	#define TOWNCENTER_PRICE 600
	#define VILLAGER_PRICE 50
	#define WARRIOR_PRICE 60

	#define MAX_TRANSPORTED_RESSOURCES 20
	#define DELAY 50

  struct Tile {
    sf::Vector2f position;
    std::shared_ptr<Tile> parent;
    int strength;
  };
  
  enum class Work { Woodcutter, Architect, Explorer, Rabbit, Harvester, Waiter, Warrior, MaxWork };
  
  template<typename T> std::vector<T> remove(std::vector<T> vect, int index);
  
  struct Human_Entity {
    unsigned action;
    unsigned count;
    Work state;
    
   	sf::Vector2f position;
   	
    bool isAlive;
  };
  
  struct Base {
  	Game game;
  	sf::Vector2f pos;
  	unsigned index;
  };
  
	#define QUIT_FIRST_STATE 7

  class IA {
   public:
    IA(Game& game, sf::Color color);
    
    /****************************/
    /*Lancement et arrêt de l'IA*/
    /****************************/
    void run(Game& game);
    void close();
    
    /***********************************/
    /*Utilisation des actions de player*/
    /***********************************/
    bool collect(Game& game, int index);
    bool store(Game& game, int index);
    void move(Game& game, const sf::Vector2f pos, int index);
    bool construct(Game& game, BuildingType type, int index);

    /***************************/
    /*Déplacements des entitées*/
    /***************************/
    int toForest(Game& game, int index);
    int toHome(Game& game, int index);
    int toFortPosition(Game& game, int index);
    int explore(Game& game, int index);
    int align(Game& game, int index);
    bool goTo(Game& game, const sf::Vector2f pos, int index);

    /*****************************/
    /*Trouver une case sur la map*/
    /*****************************/
    sf::Vector2f findFreeTree(Game& game, const sf::Vector2f pos, int index);
    sf::Vector2f findTown(Game& game, const sf::Vector2f pos, int index);
    sf::Vector2f findFortPosition(Game& game, const sf::Vector2f pos, int index);
   	sf::Vector2f computePosition(Game& game, const sf::Vector2f pos, int index);
   	sf::Vector2f computeWarriorPosition(Game& game, const sf::Vector2f pos, int index);
   	sf::Vector2f computeWarriorPositionEnnemi(Game& game, const sf::Vector2f pos, int index);
   	sf::Vector2f search(Game& game, const sf::Vector2f pos, int index);
    sf::Vector2f findEnnemi(Game& game, const sf::Vector2f pos, int index);
    sf::Vector2f findEnnemiBuilding(Game& game, const sf::Vector2f pos, int index);
    sf::Vector2f pathfinder(Game& game, const sf::Vector2f pos, int index);

    /**************************************/
    /*Calculs des points autour de la case*/
    /**************************************/
    void computePoints(Game& game, const sf::Vector2f pos,
                       std::vector<sf::Vector2f>& aroundPoints);
    void computePoints(Game& game, const sf::Vector2f pos,
                       std::vector<Tile>& aroundPoints, const Tile parent,
                       const sf::Vector2f finale);
    /*********/
    /*Calculs*/
    /*********/
    int manhattan(int x1, int y1, int x2, int y2);
    int manhattan(const sf::Vector2f pos1, const sf::Vector2f pos2);
    sf::Vector2f minManhattan(const sf::Vector2f pos1, const sf::Vector2f pos2, const sf::Vector2f start);

    /****************************/
    /*Vérifications de positions*/
    /****************************/
    bool isTileFree(Game& game, const sf::Vector2f pos);
    bool isAroundFree(Game& game, const sf::Vector2f pos, unsigned index);
    bool posInMap(Game& game, const sf::Vector2f pos);
    bool pointExist(const sf::Vector2f pos, std::vector<sf::Vector2f> aroundMap);
    bool pointExist(Tile firstTile, std::vector<Tile> aroundMap);
		bool isPlayer(Game& game, const sf::Vector2f pos, int index);
    bool isBuilding(Game& game, const sf::Vector2f pos);
    bool isFree(Game& game, const sf::Vector2f pos, int index);
    bool isGround(Game& game, const sf::Vector2f pos);
    bool isEnnemy(Game& game, const sf::Vector2f pos);
    
    /*******************/
    /*Fonctions tierces*/
    /*******************/
    void changeState(Work work, int index);
    void changeAction(int act, int index);
    std::string int2Str(int x);

    /***********************/
    /*Fonctions à supprimer*/
    /***********************/
    void pause(unsigned time);
    void printTile(Tile tile);
    void printArray(std::vector<Tile> array);
    void printArray(std::vector<sf::Vector2f> array);
    void printBuilding(sf::Vector2f pos, sf::Vector2f size);
    void printInfos(Game& game);

   private:
    sf::Color mColor;
    sf::RenderWindow window;
    sf::Vector2f start;
    
    std::vector<Human_Entity> mEntities;
    
    unsigned villagerLimit;
    unsigned warriorLimit;
    unsigned fort;
    unsigned townCenter;
    unsigned wood;

    sf::Clock clock;
    sf::Time delay;
    
    bool stopWarriors;
    
    int test;
    bool verify;
  };

  #endif
