#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h" //StudentWorld inherits from GameWorld
#include <string>
#include <vector>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    Actor* getGhostRacer() { return m_ghostRacer; }
    Actor* closestInLane(); //add two new white border lines
    //between the three lanes (at x = ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH/3, and x = ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH/3)
    //void endLevel() { return GWSTATUS_PLAYER_DIED; } //for human ped

private:
    Actor* m_ghostRacer;
    std::vector<Actor*> m_actorVec;
    
    void removeDeadActors();
    void addNewActors();
    void updateDisplayText();
    
    double m_lastWhite;
};

#endif // STUDENTWORLD_H_
