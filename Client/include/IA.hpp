  #ifndef IA_HPP
  #define IA_HPP

  #include <SFML/Graphics.hpp>
  #include <cmath>
  #include <fstream>
  #include <iostream>
  #include <memory>
  #include <string>
  #include <vector>
  #include "Game.hpp"

  struct Tile {
    sf::Vector2f position;
    std::shared_ptr<Tile> parent;
    int strength;
  };

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

    /***************************/
    /*Déplacements des entitées*/
    /***************************/
    int toForest(Game& game, int index);
    int toHome(Game& game, int index);
    bool goTo(Game& game, const sf::Vector2f pos, int index);

    /*****************************/
    /*Trouver une case sur la map*/
    /*****************************/
    sf::Vector2f findFreeTree(Game& game, const sf::Vector2f pos, int index);
    sf::Vector2f findTown(Game& game, const sf::Vector2f pos, int index);
    
    /************************************************/
    /*Trouver la prochane case lors d'un déplacement*/
    /************************************************/
    sf::Vector2f findNextTile(Game& game, const sf::Vector2f pos, int index);

    /**************************************/
    /*Calculs des points autour de la case*/
    /**************************************/
    void computePoints(Game& game, const sf::Vector2f pos,
                       std::vector<sf::Vector2f>& aroundPoints);
    /*********/
    /*Calculs*/
    /*********/
    int manhattan(int x1, int y1, int x2, int y2);
    int manhattan(const sf::Vector2f pos1, const sf::Vector2f pos2);

    /****************************/
    /*Vérifications de positions*/
    /****************************/
    bool isFree(Game& game, const sf::Vector2f pos);
    bool isTileFree(Game& game, const sf::Vector2f pos);
    bool posInMap(Game& game, const sf::Vector2f pos);
    bool pointExist(const sf::Vector2f pos, std::vector<sf::Vector2f> aroundMap);

    /*******************/
    /*Pause à supprimer*/
    /*******************/
    void pause(unsigned time);

   private:
    std::shared_ptr<Game> mGame;
    sf::Color mColor;

    std::vector<unsigned> action;
    std::vector<unsigned> state;
    std::vector<unsigned> count;

    sf::Clock clock;
    sf::Time delay;
    std::vector<sf::Vector2f> mPosition;
  };

  #endif
