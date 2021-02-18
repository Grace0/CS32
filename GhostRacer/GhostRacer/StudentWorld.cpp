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
    m_lastWhite = 0;
}

int StudentWorld::init()
{
    //yellow border lines //StudentWorld can't have a data member that's a pointer to a single border line object
    for (int n = 0; n < VIEW_HEIGHT/SPRITE_HEIGHT; n++) {
        m_actorVec.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE, n * SPRITE_HEIGHT, this));
        m_actorVec.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, n * SPRITE_HEIGHT, this));
    }
    //white border lines
    for (int m = 0; m < VIEW_HEIGHT/(4*SPRITE_HEIGHT); m++) {
        m_actorVec.push_back(new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3, m * 4*SPRITE_HEIGHT, this));
        m_actorVec.push_back(new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3, m * 4*SPRITE_HEIGHT, this));
        m_lastWhite = m_actorVec[m_actorVec.size()-1]->getY();
    }
    
    m_ghostRacer = new GhostRacer(this);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{

    double new_border_y = VIEW_HEIGHT-SPRITE_HEIGHT;
    
    //m_lastWhite = m_actorVec[m_actorVec.size()-1]->getY();
    double delta_y = new_border_y - (m_lastWhite + 4 + m_ghostRacer->getSpeed());
    
    if (delta_y >= SPRITE_HEIGHT) {
        m_actorVec.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE, new_border_y, this));
        m_actorVec.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, new_border_y, this));
        
    }
    
    if (delta_y >= 4*SPRITE_HEIGHT) {
        m_actorVec.push_back(new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3, new_border_y, this));
        m_actorVec.push_back(new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3, new_border_y, this));
        m_lastWhite = m_actorVec[m_actorVec.size()-1]->getY();
    }

    // The term "actors" refers to all actors, Ghost Racer, pedestrians,
     // vehicles, goodies, oil slicks, holy water, spray, lost souls, etc.
     // Give each actor a chance to do something, including Ghost Racer
  //  for (std::vector<Actor*>::iterator i = actorVec.begin(); i != actorVec.end(); i++) { //    for each of the actors in the game world
   // }
    
    for (int i = 0; i < m_actorVec.size(); i++) {
        if (m_actorVec[i]->isAlive()) {
            m_actorVec[i]->doSomething();
        }
    }

    if (!m_ghostRacer->isAlive()) return GWSTATUS_PLAYER_DIED;
    
    
//    if (Ghost Racer completed the currentLevel)
//    {
//    add bonus points to the score
//    return GWSTATUS_FINISHED_LEVEL;
//    }
//     }
//    }
    
    //     // Remove newly-dead actors after each tick
    //    Remove and delete dead game objects
    for (std::vector<Actor*>::iterator it = m_actorVec.begin(); it != m_actorVec.end(); ) {
        if (!(*it)->isAlive()) {
            delete *it; //free the memory
            it = m_actorVec.erase(it); //remove from the container
        } else { //increment "it"
            it++;
        }
    }

//     // Potentially add new actors to the game
//     // (e.g., oil slicks or goodies or border lines)
//    Add new actors
//     // Update the Game Status Line
//    Update display text // update the score/lives/level text at screen top
//     // the player hasn’t completed the current level and hasn’t died, so
//     // continue playing the current level

    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_ghostRacer;
    
    for (std::vector<Actor*>::iterator it = m_actorVec.begin(); it != m_actorVec.end(); it++) {
        delete *it; // delete what "it" points to
        it = m_actorVec.erase(it); //"it" now points to the next element of the vector
    }
}
