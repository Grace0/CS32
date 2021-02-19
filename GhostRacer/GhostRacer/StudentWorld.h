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

private:
    Actor* m_ghostRacer;
    std::vector<Actor*> m_actorVec;
    
    double m_lastWhite;
};

#endif // STUDENTWORLD_H_
