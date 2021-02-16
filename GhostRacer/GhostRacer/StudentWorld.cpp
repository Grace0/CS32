#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

const int LEFT_EDGE = ROAD_CENTER-ROAD_WIDTH/2;
const int RIGHT_EDGE = ROAD_CENTER+ROAD_WIDTH/2;

GameWorld* createStudentWorld(string assetPath) //called in main.cpp
{
	return new StudentWorld(assetPath); //returning a pointer to an object of itself?
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    //yellow border lines //StudentWorld can't have a data member that's a pointer to a single border line object
    for (int n = 0; n < VIEW_HEIGHT/SPRITE_HEIGHT; n++) {
        BorderLine* leftBorderLine = new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE, n * SPRITE_HEIGHT);
        actorVec.push_back(leftBorderLine);
        BorderLine* rightBorderLine = new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, n * SPRITE_HEIGHT);
        actorVec.push_back(rightBorderLine);
    }
    //white border lines
    for (int m = 0; m < VIEW_HEIGHT/(4*SPRITE_HEIGHT); m++) {
        BorderLine* leftBorderLine = new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3, m * 4*SPRITE_HEIGHT);
        actorVec.push_back(leftBorderLine);
        BorderLine* rightBorderLine = new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3, m * 4*SPRITE_HEIGHT);
        actorVec.push_back(rightBorderLine);
    }
    
   ghostRacer = new GhostRacer(this);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{

    // The term "actors" refers to all actors, Ghost Racer, pedestrians,
     // vehicles, goodies, oil slicks, holy water, spray, lost souls, etc.
     // Give each actor a chance to do something, including Ghost Racer
  //  for (std::vector<Actor*>::iterator i = actorVec.begin(); i != actorVec.end(); i++) { //    for each of the actors in the game world
   // }
    
    for (int i = 0; i < actorVec.size(); i++) {
        if (actorVec[i]->isAlive()) {
            actorVec[i]->doSomething();
        }
    }
//    {
//     if (the actor is still active/alive)
//     {
//     // tell that actor to do something (e.g. move)
//     the actor->doSomething();
//    if (Ghost Racer was destroyed during this tick)
//    return GWSTATUS_PLAYER_DIED;
//    if (Ghost Racer completed the currentLevel)
//    {
//    add bonus points to the score
//    return GWSTATUS_FINISHED_LEVEL;
//    }
//     }
//    }
//     // Remove newly-dead actors after each tick
//    Remove and delete dead game objects
//     // Potentially add new actors to the game
//     // (e.g., oil slicks or goodies or border lines)
//    Add new actors
//     // Update the Game Status Line
//    Update display text // update the score/lives/level text at screen top
//     // the player hasn’t completed the current level and hasn’t died, so
//     // continue playing the current level
//    return GWSTATUS_CONTINUE
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete ghostRacer;
}
