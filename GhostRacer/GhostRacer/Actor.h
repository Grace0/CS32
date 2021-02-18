#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h" //to include imageID's
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
    }
    virtual ~Actor() {} //virtual so that subclass' destructors get called; note that subclasses get destructed first
 
    StudentWorld* getWorld() { return m_studentWorld; }
    bool isAlive() { return m_isAlive; }
    bool doOverlap(Actor* otherActor);
//    1. Compute the delta_x between A and B (which is the absolute value of the distance between A’s center x coordinate and B’s center x coordinate).
//    2. Compute the delta_y between A and B (which is the absolute value of the distance between A’s center y coordinate and B’s center y coordinate).
//    3. Compute the sum of the radiuses of A and B. While most of our graphics are rectangular, you can treat them a bit like a circle to simplify things.
//    4. If delta_x < radius_sum*.25 AND delta_y < radius_sum*.6 then the two objects
//    2 are said to overlap .
    virtual bool collisionAvoidanceWorthy() { return true; }
    
    virtual void doSomething() = 0;
    virtual void activate() {}
    virtual void doDamage() {} //?
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
    
    virtual void doSomething() {
        if (!isAlive()) return;
//        If the Ghost Racer overlaps with me on the road, then Damage the player by 5 hit points
//        Set my alive state to false
//        Else if I still want to wander in the same direction Move one pixel in my chosen wandering direction
//        Else if I’m done wandering in the same direction Pick a new direction to wander
//        Pick a new number of ticks to wander in that direction Else if I have fallen off the bottom of the screen
//        Set my alive state to false Else ...
    }

    virtual ~Pedestrian();
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
};

class GhostRacer : public Actor { //GhostRacer is derived from Actor
public:
    GhostRacer(StudentWorld *studentWorld);
    virtual ~GhostRacer() {} //virtual functions must be defined (Even if they're empty)
    
    double getSpeed() { return m_speed; } 
    virtual bool collisionAvoidanceWorthy() { return true; }
    
    void move();
    virtual void doSomething();
private:
    double m_speed;
    double m_direction;
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
    double m_vertSpeed, m_horizSpeed;
    bool m_isAlive;
};

#endif // ACTOR_H_
