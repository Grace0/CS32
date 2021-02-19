#include "Actor.h"
#include "StudentWorld.h" //getWorld()->anything is used in function implementations
#include <cmath>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

bool Actor::doOverlap(Actor* otherActor) {
    double delta_x = abs(getX() - otherActor->getX());
    double delta_y = abs(getY() - otherActor->getY());
    double radius_sum = getRadius() + otherActor->getRadius();
    if (delta_x < radius_sum*.25 && delta_y < radius_sum*.6) {
        return true;
    }
    return false;
}

GhostRacer::GhostRacer(StudentWorld *studentWorld) : Actor(IID_GHOST_RACER, 128, 32, 90, 4.0, 0, studentWorld) {
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
       //         move();
            }
            break;
        case KEY_PRESS_RIGHT:
            if (getDirection() > 66) {
                setDirection(getDirection()-8);
         //       move();
            }
            break;
        case KEY_PRESS_UP:
            if (getVertSpeed() < 5) {
                setVertSpeed(getVertSpeed()+1);
         //       move();
            }
            break;
        case KEY_PRESS_DOWN:
            if (getVertSpeed() > -1) {
                setVertSpeed(getVertSpeed()-1);
         //       move();
            }
            break;
        case KEY_PRESS_SPACE:
      //  ... add spray in front of Ghost Racer...;
            break;
    }
        
        
    
    }
    
    move(); //regardless of whether the player hit a key, GR should move for the give tick
}

void GhostRacer::move() {
    const double max_shift_per_tick = 4.0;
    double direction = getDirection() * 3.14 / 180.0;
    double delta_x = cos(direction) * max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    moveTo(cur_x + delta_x, cur_y);
}

BorderLine::BorderLine(int imageID, double startX, double startY, StudentWorld* studentWorld): Actor(imageID, startX, startY, 0, 2.0, 2.0, studentWorld) {
    m_isAlive = true;
    setVertSpeed(-4);
    setHorizSpeed(0);
}

void BorderLine::doSomething() {
    useMoveAlg();
}

void Actor::useMoveAlg() {
    double vert_speed = m_vertSpeed - getWorld()->getGhostRacer()->getVertSpeed(); //temporary variable; shouldn't be changing m_vertSpeed itself each loop because that would make the speed keep changing
    double new_y = getY() + vert_speed;
    double new_x = getX() + m_horizSpeed;
    moveTo(new_x, new_y);
    
    if (getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT) {
        m_isAlive = false;
        return;
    }
}

void Pedestrian::doSomething() {
    if (!isAlive()) return;
    
    if (doOverlap(getWorld()->getGhostRacer())) {
        getWorld()->getGhostRacer()->receiveDamage(5);
        receiveDamage(2);
        return;
    }
    
    if (((getX() - getWorld()->getGhostRacer()->getX()) <= 30) && (getY() > getWorld()->getGhostRacer()->getY())) {
        setDirection(270);
        if (getX() > getWorld()->getGhostRacer()->getX()) {
            m_horizSpeed = -1;
        } else if (getX() < getWorld()->getGhostRacer()->getX()) {
            m_horizSpeed = 1;
        } else {
            m_horizSpeed = 0;
        }
    }
    
    useMoveAlg();
    
    if (m_movementPlanDis > 0) {
        m_movementPlanDis--;
        return;
    } else {
        
        double new_horiz_speed = randInt(-3, 3);
        while (new_horiz_speed == 0) {
            new_horiz_speed = randInt(-3, 3);
        }

        setHorizSpeed(new_horiz_speed);
        m_movementPlanDis = randInt(4, 32);
        if (getHorizSpeed() < 0) {
            setDirection(180);
        } else {
            setDirection(0);
        }
    }
}

void Pedestrian::receiveDamage(int hitPoints) {
   m_hitPoints -= hitPoints;
   if (m_hitPoints <= 0) {
       setToDead();
       //getWorld()->playSound(SOUND_PED_DIE);
       if (doOverlap(getWorld()->getGhostRacer())) {
           //add new healing goodie in its current position
       }
           //ensure the player receives 150 points
   } else {
       //getWorld()->playSound(SOUND_PED_HURT);
   }
}

void ZombiePed::doSomething() {
   if (!isAlive()) return;
   
   if (doOverlap(getWorld()->getGhostRacer())) {
       getWorld()->getGhostRacer()->receiveDamage(5);
       receiveDamage(2);
       return;
   }
   
   if (((getX() - getWorld()->getGhostRacer()->getX()) <= 30) && (getY() > getWorld()->getGhostRacer()->getY())) {
       setDirection(270);
       if (getX() > getWorld()->getGhostRacer()->getX()) {
           setHorizSpeed(-1);
       } else if (getX() < getWorld()->getGhostRacer()->getX()) {
           setHorizSpeed(1);
       } else {
           setHorizSpeed(0);
       }
       m_ticksUntilGrunt--;
       if (m_ticksUntilGrunt <= 0) {
           //getWorld()->playSound(SOUND_ZOMBIE_ATTACK);
           m_ticksUntilGrunt = 20;
       }
   }
}
