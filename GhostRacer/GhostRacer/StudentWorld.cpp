#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath); //returning a pointer to an object of itself?
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    createStudentWorld(assetPath);
}

int StudentWorld::init()
{
//create border lines
   ghostRacer = new GhostRacer(this);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    ghostRacer->doNothing();
//    decLives();
    
    // The term "actors" refers to all actors, Ghost Racer, pedestrians,
     // vehicles, goodies, oil slicks, holy water, spray, lost souls, etc.
     // Give each actor a chance to do something, including Ghost Racer
//    for each of the actors in the game world
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
//    return GWSTATUS_CONTINU
    
    return 1;//GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    delete ghostRacer;
}
