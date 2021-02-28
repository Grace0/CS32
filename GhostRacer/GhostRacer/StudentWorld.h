#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h" //StudentWorld inherits from GameWorld
#include <string>
#include <vector>

class Actor; //use pointers to these classes
class GhostRacer;
class HolyWaterProjectile;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    GhostRacer* getGhostRacer();
    Actor* closestInLane(int laneNum, double y);
   // Actor* closestInLane(int laneNum, bool inFront);
    Actor* getProjectileOverlap(HolyWaterProjectile* proj);
    void addHealingGoodie(double startX, double startY);
    void addOilSlick(double startX, double startY);
    void addHolyWaterSpray(double startX, double startY, int startDirection);
    
    void incNumSaved();

private:
    GhostRacer* m_ghostRacer;
    std::vector<Actor*> m_actorVec;
    
    void removeDeadActors();
    void addNewActors();
    void updateDisplayText();
    
    int getHealth();
    int getSouls2Save();
    int getSprays();
    int getBonus();
    
    int getLaneCoord(int laneNum);
    void addZombieCab();
    
    double m_lastWhite;
    int m_numSaved;
    int m_bonusPoints;
};

#endif // STUDENTWORLD_H_
