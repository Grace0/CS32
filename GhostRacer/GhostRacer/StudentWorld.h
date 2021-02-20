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
    Actor* closestInLane(int laneNum, double y, bool inFront); //add two new white border lines
    void addPoints(int numPoints);
    //between the three lanes (
    //void endLevel() { return GWSTATUS_PLAYER_DIED; } //for human ped

private:
    Actor* m_ghostRacer;
    std::vector<Actor*> m_actorVec;
    
    void removeDeadActors();
    void addNewActors();
    void updateDisplayText();
    
    double m_lastWhite;
    int m_playerPoints;
};

#endif // STUDENTWORLD_H_
