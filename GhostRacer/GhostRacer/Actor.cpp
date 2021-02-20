#include "Actor.h"
#include "StudentWorld.h" //getWorld()->anything is used in function implementations
#include <cmath>

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
            }
            break;
        case KEY_PRESS_RIGHT:
            if (getDirection() > 66) {
                setDirection(getDirection()-8);
            }
            break;
        case KEY_PRESS_UP:
            if (getVertSpeed() < 5) {
                setVertSpeed(getVertSpeed()+1);
            }
            break;
        case KEY_PRESS_DOWN:
            if (getVertSpeed() > -1) {
                setVertSpeed(getVertSpeed()-1);
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
    setVertSpeed(-4);
    setHorizSpeed(0);
}

void BorderLine::doSomething() {
   useMoveAlg();
}

bool Actor::useMoveAlg() {
    double vert_speed = m_vertSpeed - getWorld()->getGhostRacer()->getVertSpeed(); //temporary variable; shouldn't be changing m_vertSpeed itself each loop because that would make the speed keep changing
    double new_y = getY() + vert_speed;
    double new_x = getX() + m_horizSpeed;
    moveTo(new_x, new_y);
    
    if (getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT) {
        m_isAlive = false;
        return false;
    } else {
        return true;
    }
}

void ZombiePed::grunt() {
   if (((getX() - getWorld()->getGhostRacer()->getX()) <= 30) && (getY() > getWorld()->getGhostRacer()->getY())) {
       setDirection(270);
       if (getX() > getWorld()->getGhostRacer()->getX()) {
           setHorizSpeed(-1);
       } else if (getX() < getWorld()->getGhostRacer()->getX()) {
           setHorizSpeed(1);
       } else {
           setHorizSpeed(0);
       }
   }
}

void Pedestrian::doSomething() {
    if (!isAlive()) return;
    
    if (doOverlap(getWorld()->getGhostRacer())) {
        handleOverlap();
        return;
    }
    
    grunt();
    
    if (!useMoveAlg()) return;
    
    //zombieCabs and zombiePeds decrement first...?
    m_movementPlanDis--;
    if (m_movementPlanDis > 0) {
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

void HumanPed::handleOverlap() {
   getWorld()->decLives();
   getWorld()->getGhostRacer()->setToDead();
}

void ZombiePed::handleOverlap() {
    getWorld()->getGhostRacer()->receiveDamage(5);
    receiveDamage(2);
}

void ZombieCab::receiveDamage(int hitPoints) {
    m_hitPoints -= hitPoints;
    if (m_hitPoints <= 0) {
        setToDead();
        getWorld()->playSound(SOUND_VEHICLE_DIE);
        if (randInt(0, 4) == 0) {
            //add a new healing goodie at getX() getY()
        }
        getWorld()->addPoints(200);
        return;
    } else {
        getWorld()->playSound(SOUND_VEHICLE_HURT);
    }
}

void Pedestrian::receiveDamage(int hitPoints) {
   m_hitPoints -= hitPoints;
   if (m_hitPoints <= 0) {
       setToDead();
       getWorld()->playSound(SOUND_PED_DIE);
       if (doOverlap(getWorld()->getGhostRacer())) {
           //add new healing goodie in its current position
       }
       getWorld()->addPoints(150);
   } else {
       getWorld()->playSound(SOUND_PED_HURT);
   }
}

void ZombieCab::doSomething() {
    if (!isAlive()) return;
    
    if (doOverlap(getWorld()->getGhostRacer())) {
        if (m_hasOverlapped) {
            
        } else {
            getWorld()->playSound(SOUND_VEHICLE_CRASH);
            getWorld()->getGhostRacer()->receiveDamage(20);
            
            if (getX() <= getWorld()->getGhostRacer()->getX()) {
                setHorizSpeed(-5);
                setDirection(120 + randInt(0, 20-1));
            } else {
                setHorizSpeed(5);
                setDirection(60 - randInt(0, 20-1));
            }
            m_hasOverlapped = true;
        }
        
        if (!useMoveAlg()) return;
        
        if ((getVertSpeed() > getWorld()->getGhostRacer()->getVertSpeed())) {
           // getWorld()->closestInLane(getLaneNum(), getY(), true);
        } else {
           // getWorld()->closestInLane(getLaneNum(), getY(), false);
        }
        
        //Movement plan
        if (m_movementPlanDis > 0) {
            m_movementPlanDis--;
            return;
        } else {
            
            double added_speed = randInt(-2, 2);
            setVertSpeed(getVertSpeed() + added_speed);
            m_movementPlanDis = randInt(4, 32);
        }
        
    }
}

void GhostRacer::receiveDamage(int hitPoints) {
   m_hitPoints -= hitPoints;
   if (m_hitPoints <= 0) {
       setToDead();
       getWorld()->playSound(SOUND_PLAYER_DIE);
   }
}

int Actor::getLaneNum() {
    int x = getX();
   
    if (x < ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH/3) { //leftmost lane
        return 1;
    } else if (x > ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH/3) { //rightmost lane
        return 2;
    } else { //center lane
        return 3;
    }
}

void Goodie::doSomething() {
    useMoveAlg();
    
    if (doOverlap(getWorld()->getGhostRacer())) {
        handleOverlap();
    }
}

void OilSlick::handleOverlap() {
    getWorld()->playSound(SOUND_OIL_SLICK);
    getWorld()->getGhostRacer()->spin();
}

void HolyWaterGoodie::handleOverlap() {
    getWorld()->getGhostRacer()->addWater(10);
    setToDead();
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->addPoints(50);
}

void GhostRacer::spin() {
    
    double new_dir = randInt(5,20);
    
    if (randInt(0, 1) == 0) { //50-50 chance that GR will spin the other dir
        new_dir *= -1;
    }
    
    if ((getDirection() + new_dir) >= 60 && (getDirection() + new_dir) <= 120) {
        setDirection(new_dir);
    }

}

void GhostRacer::addWater(int charge) {
    m_holyWaterUnits += charge;
}

void SoulGoodie::handleOverlap() {
    getWorld()->incNumSaved();
    setToDead();
    getWorld()->playSound(SOUND_GOT_SOUL);
    getWorld()->addPoints(100);
}
