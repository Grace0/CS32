//
//  Game.hpp
//  CS32
//
//  Created by Grace Kwak on 1/9/21.
//

#ifndef Game_h
#define Game_h

#include "globals.h"
#include "City.h"

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();

        // Mutators
    void play();
    
    int decodeDirection(char dir);

  private:
    City* m_city;
};

#endif /* Game_hpp */
