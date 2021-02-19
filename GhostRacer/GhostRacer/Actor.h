#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h" //Actor inherits from GraphObject
#include "GameConstants.h" //to include imageID's
//#include "StudentWorld.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//GraphObject functions
//GraphObject(int imageID, double startX, double startY,
//    int startDirection = 0, double size = 1.0, int depth = 0);

//    double getX() const; // in pixels (0-255)
//    double getY() const; // in pixels (0-255)
//    void moveTo(double x, double y); // in pixels (0-255)
//     // moveForward() moves the actor the specified number of units in the
//     // direction it is facing.
//    void moveForward(int units = 1);
//     // getPositionInThisDirection() returns a new (x, y) location in the
//     // specified direction and distance, based on the passed-in angle and the
//     // GraphObject’s current (x, y) location.
//    void getPositionInThisDirection(int angle, int units,
//     double& dx, double& dy);
//    int getDirection() const; // in degrees (0-359)
//    void setDirection(int d); // in degrees (0-359)

class StudentWorld; //since Actor uses a pointer to a StudentWorld

class Actor : public GraphObject { //Actor is derived from GraphObject

public:
    Actor(int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld* studentWorld) : GraphObject(imageID, startX, startY, startDirection, size, depth) { //default params at the end
        m_studentWorld = studentWorld;
        m_isAlive = true;
        m_vertSpeed = 0;
        m_horizSpeed = 0;
    }
    virtual ~Actor() {} //virtual so that subclass' destructors get called; note that subclasses get destructed first
 
    StudentWorld* getWorld() { return m_studentWorld; }
    bool isAlive() { return m_isAlive; }
    void setToDead() { m_isAlive = false; }
    bool doOverlap(Actor* otherActor);
    void useMoveAlg();

    virtual bool collisionAvoidanceWorthy() { return true; }
    
    virtual double getVertSpeed() { return m_vertSpeed; }
    virtual void setVertSpeed(double vertSpeed) { m_vertSpeed = vertSpeed; }
    
    virtual double getHorizSpeed() { return m_horizSpeed; }
    virtual void setHorizSpeed(double horizSpeed) { m_horizSpeed = horizSpeed; }
    
    virtual void doSomething() = 0;
    virtual void activate() {}
    virtual void receiveDamage(int damage) {
    } //?
private:
    StudentWorld* m_studentWorld;
    bool m_isAlive;
    double m_vertSpeed, m_horizSpeed;
};

class Pedestrian : public Actor {
public:
    Pedestrian(int imageID, double startX, double startY, double size, StudentWorld* studentWorld) : Actor(imageID, startX, startY, 0, size, 0, studentWorld) { //direction=0, depth=0
        m_movementPlanDis = 0;
        m_vertSpeed = -4.0;
        m_horizSpeed = 0.0;
        m_hitPoints = 2;
    }
    
    double getVertSpeed() {
        return m_vertSpeed;
    }
    double getHorizSpeed() {
        return m_horizSpeed;
    }
    void setHorizSpeed(double horizSpeed) {
        m_horizSpeed = horizSpeed;
    }
    void setVertSpeed(double vertSpeed) {
        m_vertSpeed = vertSpeed;
    }
    
    virtual void doSomething();
    
    virtual void receiveDamage(int hitPoints);

    virtual ~Pedestrian() {}
    virtual bool collisionAvoidanceWorthy() { return true; }
private:
    int m_movementPlanDis;
    double m_vertSpeed, m_horizSpeed;
    int m_hitPoints;
};

class HumanPed : public Pedestrian {
public:
    HumanPed(double startX, double startY, StudentWorld* studentWorld) : Pedestrian(IID_HUMAN_PED, startX, startY, 2.0, studentWorld) {
    }
    virtual ~HumanPed();
    

private:

};

class ZombiePed : public Pedestrian {
public:
    ZombiePed(double startX, double startY, StudentWorld* studentWorld) : Pedestrian(IID_ZOMBIE_PED, startX, startY, 3.0, studentWorld) {
        m_ticksUntilGrunt = 0;
    }
    virtual ~ZombiePed();
private:
    
    int m_ticksUntilGrunt;
    
    virtual void doSomething();

};

class GhostRacer : public Actor { //GhostRacer is derived from Actor
public:
    GhostRacer(StudentWorld *studentWorld);
    virtual ~GhostRacer() {} //virtual functions must be defined (Even if they're empty)
    
    virtual bool collisionAvoidanceWorthy() { return true; }
    virtual void receiveDamage(int hitPoints) {
        m_hitPoints -= hitPoints;
        if (m_hitPoints <= 0) {
            setToDead();
            //getWorld()->playSound(SOUND_PLAYER_DIE);
        }
    }
    
    void move();
    virtual void doSomething();
private:
    int m_holyWaterUnits;
    int m_hitPoints;
};

class BorderLine : public Actor {
public:
    BorderLine(int imageID, double startX, double startY, StudentWorld* studentWorld);
    virtual ~BorderLine() {}
    
    virtual void doSomething();
    virtual bool collisionAvoidanceWorthy() { return true; }
private:
    bool m_isAlive;
};

#endif // ACTOR_H_
