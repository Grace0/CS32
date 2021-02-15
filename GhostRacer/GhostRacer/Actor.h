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
    Actor(int imageID, double startX, double startY, int startDirection = 0, double size = 1.0, int depth = 0, StudentWorld* studentWorld = nullptr) : GraphObject(imageID, startX, startY, startDirection, size, depth) { //default params at the end
        m_studentWorld = studentWorld;
    }
 
    StudentWorld* getWorld() { return m_studentWorld; }
    virtual ~Actor() {} //virtual so that subclass' destructors get called; note that subclasses get destructed first
private:
    StudentWorld* m_studentWorld;
};

class GhostRacer : public Actor { //GhostRacer is derived from Actor
public:
    GhostRacer(StudentWorld *studentWorld) : Actor(IID_GHOST_RACER, 128, 32, 90, 4.0, 0, studentWorld) {
        
    }
    virtual ~GhostRacer() {} //virtual functions must be defined (Even if they're empty)
    void doNothing() {}
private:
};

class BorderLine : public Actor {
public:
    BorderLine(int imageID, double startX, double startY) : Actor(imageID, startX, startY, 0, 2.0, 0) { }
    virtual ~BorderLine();
private:
};

#endif // ACTOR_H_
