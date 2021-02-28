#include "Actor.h"
#include "StudentWorld.h" //getWorld()->anything is used in function implementations
#include <cmath>

//Actor class implementations
bool Actor::doOverlap(Actor* otherActor) {
    double delta_x = abs(getX() - otherActor->getX());
    double delta_y = abs(getY() - otherActor->getY());
    double radius_sum = getRadius() + otherActor->getRadius();
    if (delta_x < radius_sum*.25 && delta_y < radius_sum*.6) {
        return true;
    }
    return false;
}

bool Actor::useMoveAlg() {
    double vert_speed = m_vertSpeed - getWorld()->getGhostRacer()->getVertSpeed();
    double new_y = getY() + vert_speed;
    double new_x = getX() + m_horizSpeed;
    moveTo(new_x, new_y);
    
    return isWithinBounds(getX(), getY());

}

bool Actor::isWithinBounds(double x, double y) {
    if (x < 0 || y < 0 || x > VIEW_WIDTH || y > VIEW_HEIGHT) {
        m_isAlive = false;
        return false;
    } else {
        return true;
    }
}


int Actor::getLaneNum() {
    double x = getX();
    
    if (x < ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH/3) { //leftmost lane
        return 0;
    } else if (x >= ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH/3) { //rightmost lane
        return 2;
    } else { //center lane
        return 1;
    }
}

//Active class implementations
int Active::getHealth() {
    return m_hitPoints;
}

void Active::addHealth(int health) {
    m_hitPoints += health;
    if (m_hitPoints > 100) m_hitPoints = 100; //max
}

//Goodie class implementations
void Goodie::doSomething() {
    useMoveAlg();
    
    if (doOverlap(getWorld()->getGhostRacer())) {
        handleOverlap();
    }
}

//Oil Slick class implementations
void OilSlick::handleOverlap() {
    getWorld()->playSound(SOUND_OIL_SLICK);
    getWorld()->getGhostRacer()->spin();
}

//Healing Goodie class implementations
void HealingGoodie::handleOverlap() {
    getWorld()->getGhostRacer()->addHealth(10);
    setToDead();
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->increaseScore(250);
}

//Holy Water Goodie class implementations
void HolyWaterGoodie::handleOverlap() {
    getWorld()->getGhostRacer()->addWater(10);
    setToDead();
    getWorld()->playSound(SOUND_GOT_GOODIE);
    getWorld()->increaseScore(50);
}

//Soul Goodie class implementations
void SoulGoodie::handleOverlap() {
    getWorld()->incNumSaved();
    setToDead();
    getWorld()->playSound(SOUND_GOT_SOUL);
    getWorld()->increaseScore(100);
}

void SoulGoodie::doSomething() {
   
    Goodie::doSomething();
    
    setDirection(getDirection()+10);
}

//Borderline class implementations
void BorderLine::doSomething() {
   useMoveAlg();
}

//HolyWaterProjectile class implementations
void HolyWaterProjectile::doSomething() {
    if (!isAlive()) return;
    
    Actor* overlapped = getWorld()->getProjectileOverlap(this);
    
    if (overlapped != nullptr) {
        overlapped->receiveDamage(1);
        setToDead();
        return;
    } else {
        moveForward(SPRITE_HEIGHT);
        m_curTravDis += SPRITE_HEIGHT;
    }
    
    if (!isWithinBounds(getX(), getY()) || m_curTravDis >= m_maxTravDis) {
        setToDead();
        return;
    }
    
}


//Pedestrian class implementations
void Pedestrian::selectMovementPlan() {
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

void Pedestrian::doSomething() {
    if (!isAlive()) return;
    
    if (doOverlap(getWorld()->getGhostRacer())) {
        if (handleOverlap()) { //zombie ped or human ped's handleOverlaps return true
            return;
        }
        
    }
    
    grunt(); //Only zombie ped
    
    if (!useMoveAlg()) return;
    
    if (adjustSpeed()) return; //only zombie cab
    
    selectMovementPlan();

}

//HumanPed class implementations
bool HumanPed::handleOverlap() {
   getWorld()->decLives();
   getWorld()->getGhostRacer()->setToDead();
   return true;
}
void HumanPed::receiveDamage(int hitPoints) {
    setHorizSpeed(getHorizSpeed() * -1);
    if (getHorizSpeed() < 0) { //negative speed faces left
        setDirection(180);
    } else {
        setDirection(0); //positive speed faces right
    }
    getWorld()->playSound(SOUND_PED_HURT);
    
}

//ZombiePed class implementations
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

bool ZombiePed::handleOverlap() {
    getWorld()->getGhostRacer()->receiveDamage(5);
    receiveDamage(2);
    return true;
}

void ZombiePed::receiveDamage(int hitPoints) {
    addHealth(-hitPoints);
   if (getHealth() <= 0) {
       setToDead();
       getWorld()->playSound(SOUND_PED_DIE);
       if (!doOverlap(getWorld()->getGhostRacer()) && (randInt(0, 4) == 0)) {
           getWorld()->addHealingGoodie(getX(), getY());
       }
       getWorld()->increaseScore(150);
   } else {
       getWorld()->playSound(SOUND_PED_HURT);
   }
}

//ZombieCab class implementations
void ZombieCab::receiveDamage(int hitPoints) {
    addHealth(-hitPoints);
    if (getHealth() <= 0) {
        setToDead();
        getWorld()->playSound(SOUND_VEHICLE_DIE);
        if (randInt(0, 4) == 0) {
            getWorld()->addOilSlick(getX(), getY());
        }
        getWorld()->increaseScore(200);
        return;
    } else {
        getWorld()->playSound(SOUND_VEHICLE_HURT);
    }
}

bool ZombieCab::handleOverlap() {
    if (!m_hasOverlapped) {
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
    return false;
}

void ZombieCab::selectMovementPlan() {
    if (getMovementPlan() > 0) {
        setMovementPlan(getMovementPlan()-1);
        return;
    } else {
        double added_speed = randInt(-2, 2);
        setVertSpeed(getVertSpeed() + added_speed);
        setMovementPlan(randInt(4, 32));
    }
}

bool ZombieCab::adjustSpeed() {
    //extension of ZombieCab only
    Actor* closest = getWorld()->closestInLane(getLaneNum(), getY());
    if (closest == nullptr) return false; //did not adjust speed
    
        if ((getVertSpeed() > getWorld()->getGhostRacer()->getVertSpeed())) {
            if ((closest->getY() > getY()) && (abs(closest->getY() - getY()) < 96)) {
                setVertSpeed(getVertSpeed() - 0.5);
                return true;
            }
        } else {
            if ((closest->getY() < getY()) && (abs(closest->getY() - getY()) < 96)) {
                setVertSpeed(getVertSpeed() + 0.5);
                return true;
            }
        }
    
    return false;
}

//GhostRacer class implementations
void GhostRacer::doSomething() {
    if (!isAlive()) {
        return;
    }
    
    //Left lane bound
    if (getX() <= ROAD_CENTER-ROAD_WIDTH/2) {
        if (getDirection() > 90) {
            receiveDamage(10);
        }
        setDirection(82);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
    }
    
    //Right lane bound
    if (getX() >= ROAD_CENTER+ROAD_WIDTH/2) {
        if (getDirection() < 90) {
            receiveDamage(10);
        }
        setDirection(98);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
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
                if (m_holyWaterUnits >= 1) {
                    double delta_x = SPRITE_HEIGHT*cos(getDirection()*3.14/180.0);
                    double delta_y = SPRITE_HEIGHT*sin(getDirection()*3.14/180.0);
                    getWorld()->addHolyWaterSpray(getX()+delta_x, getY()+delta_y, getDirection());
                    getWorld()->playSound(SOUND_PLAYER_SPRAY);
                    m_holyWaterUnits--;
                }
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

void GhostRacer::receiveDamage(int hitPoints) {
   addHealth(-hitPoints);
   if (getHealth() <= 0) {
       setToDead();
       getWorld()->playSound(SOUND_PLAYER_DIE);
   }
}

void GhostRacer::spin() {
    
    double new_dir = randInt(5,20);
    
    if (randInt(0, 1) == 0) { //50-50 chance that GR will spin the other dir
        new_dir *= -1;
    }
    
    if ((getDirection() + new_dir) >= 60 && (getDirection() + new_dir) <= 120) {
        setDirection(getDirection() + new_dir);
    }

}

void GhostRacer::addWater(int charge) {
    m_holyWaterUnits += charge;
}

int GhostRacer::getSprays() {
    return m_holyWaterUnits;
}
