#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

GhostRacer::GhostRacer(StudentWorld *studentWorld) : Actor(IID_GHOST_RACER, 128, 32, 90, 4.0, 0, studentWorld) {
   m_speed = 0;
   m_holyWaterUnits = 10;
   m_hitPoints = 100;
}

void GhostRacer::doSomething() {
    if (!isAlive()) {
        return;
    }
    
    int ch;
    if (getWorld()->getKey(ch)) {
    switch (ch)
    {
        case KEY_PRESS_LEFT:
            if (getDirection() < 114) {
                setDirection(getDirection()+8);
                move();
            }
            break;
        case KEY_PRESS_RIGHT:
            if (getDirection() > 66) {
                setDirection(getDirection()-8);
                move();
            }
            break;
        case KEY_PRESS_UP:
            if (m_speed < 5) {
                m_speed++;
                move();
            }
            break;
        case KEY_PRESS_DOWN:
            if (m_speed > -1) {
                m_speed--;
                move();
            }
            break;
        case KEY_PRESS_SPACE:
      //  ... add spray in front of Ghost Racer...;
            break;
    }
    
    }
}

void GhostRacer::move() {
    const double max_shift_per_tick = 4.0;
    double direction = getDirection();
    double delta_x = cos(direction) * max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    moveTo(cur_x + delta_x, cur_y);
}

BorderLine::BorderLine(int imageID, double startX, double startY, StudentWorld* studentWorld): Actor(imageID, startX, startY, 0, 2.0, 2.0, studentWorld) {
    m_isAlive = true;
    m_vertSpeed = -4;
    m_horizSpeed = 0;
}

void BorderLine::doSomething() {
    m_vertSpeed = m_vertSpeed - getWorld()->getGhostRacer()->getSpeed();
    double new_y = getY() + m_vertSpeed;
    double new_x = getX() + m_horizSpeed;
    moveTo(new_x, new_y);
    
    if (getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT) {
        m_isAlive = false;
        return;
    }
    
}
