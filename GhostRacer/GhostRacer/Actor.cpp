#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

GhostRacer::GhostRacer(StudentWorld *studentWorld) : Actor(IID_GHOST_RACER, 128, 32, 90, 4.0, 0, studentWorld) {
   m_isAlive = true;
   m_speed = 0;
   m_holyWaterUnits = 10;
   m_health = 100;
}

void GhostRacer::doSomething() {
    if (!m_isAlive) {
        return;
    }
}

BorderLine::BorderLine(int imageID, double startX, double startY): Actor(imageID, startX, startY, 0, 2.0, 0) {
    m_speed = 0;
}
