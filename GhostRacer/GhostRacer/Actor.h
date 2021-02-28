#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h" //Actor inherits from GraphObject
#include "GameConstants.h" //to include imageID's

class StudentWorld; //since Actor uses a pointer to a StudentWorld

class Actor : public GraphObject {

public:
    Actor(int imageID, double startX, double startY, int startDirection, double size, int depth, double startVertSpeed, double startHorizSpeed, StudentWorld* studentWorld) : GraphObject(imageID, startX, startY, startDirection, size, depth) { //default params at the end
        m_studentWorld = studentWorld;
        m_isAlive = true;
        m_vertSpeed = startVertSpeed;
        m_horizSpeed = startHorizSpeed;
    }
    

    virtual bool collisionAvoidanceWorthy() { return true; }
    
    virtual ~Actor() {} //virtual so that subclass' destructors get called; note that subclasses get destructed first
    
    void setToDead() { m_isAlive = false; }
    double getVertSpeed() { return m_vertSpeed; }
    virtual void receiveDamage(int damage) {}
    
    virtual void doSomething() = 0;
    bool isAlive() { return m_isAlive; }
    int getLaneNum();
    virtual bool isAffectedProjectiles() = 0;
    bool doOverlap(Actor* otherActor);
    
protected:
    
    bool useMoveAlg();
    bool isWithinBounds(double x, double y);
    
    StudentWorld* getWorld() { return m_studentWorld; }
    
    virtual void setVertSpeed(double vertSpeed) { m_vertSpeed = vertSpeed; }
    
    virtual double getHorizSpeed() { return m_horizSpeed; }
    virtual void setHorizSpeed(double horizSpeed) { m_horizSpeed = horizSpeed; }
    
    
private:
    StudentWorld* m_studentWorld;
    bool m_isAlive;
    double m_vertSpeed, m_horizSpeed;
};

class Active : public Actor {
public:
    
    //for GR
    Active(StudentWorld *studentWorld) : Actor(IID_GHOST_RACER, 128, 32, 90, 4.0, 0, 0.0, 0.0, studentWorld) {
       m_hitPoints = 100;
    }
    
    //for HumPed, ZomPed, ZomCab
    Active(int imageID, double startX, double startY, int startDirection, int size, double startVertSpeed, double startHorizSpeed, int startHitPoints, StudentWorld* studentWorld) : Actor(imageID, startX, startY, startDirection, size, 0, startVertSpeed, startHorizSpeed, studentWorld) {
        m_hitPoints = startHitPoints;
    }
    
    //Setters/getters
    void addHealth(int health);
    int getHealth();
    
    //Properties
    virtual bool isAffectedProjectiles() { return true; }
    bool collisionAvoidanceWorthy() { return true; }
    
    virtual ~Active() {}
    
protected:
    //Main functions
    virtual void doSomething() = 0;
    virtual void receiveDamage(int hitPoints) = 0;
    
private:
    int m_hitPoints;
};

class Goodie : public Actor {
public:
    Goodie(int imageID, double startX, double startY, int startDirection, double size, StudentWorld* studentWorld) : Actor(imageID, startX, startY, startDirection, size, 2.0, -4.0, 0.0, studentWorld) {
        
    }
    
    //for HolyWaterProjectile
    Goodie(double startX, double startY, int startDirection, StudentWorld* studentWorld) : Actor(IID_HOLY_WATER_PROJECTILE, startX, startY, startDirection, 1.0, 1, 0.0, 0.0, studentWorld) {
        
    }

    //Properties
    virtual bool isAffectedProjectiles() { return false; }
    virtual bool collisionAvoidanceWorthy() { return false; }
    
    void receiveDamage(int damage) { setToDead(); }
    
    virtual ~Goodie() {}
    
protected:
    //Main functions
    virtual void doSomething();
    virtual void handleOverlap() {};
    
private:
};

class OilSlick : public Goodie {
public:
    OilSlick(double startX, double startY, StudentWorld* studentWorld) : Goodie(IID_OIL_SLICK, startX, startY, 0, randInt(2,5), studentWorld) {
    }
    virtual ~OilSlick() {}
    
protected:
    
private:
    virtual void handleOverlap();

};

class HealingGoodie : public Goodie {
public:
    HealingGoodie(double startX, double startY, StudentWorld* studentWorld) : Goodie(IID_HEAL_GOODIE, startX, startY, 0, 1.0, studentWorld) {
    }
    virtual ~HealingGoodie() {}
    
    virtual bool isAffectedProjectiles() { return true; }
    
protected:
    
private:
    virtual void handleOverlap();

};

class HolyWaterGoodie : public Goodie {
public:
    HolyWaterGoodie(double startX, double startY, StudentWorld* studentWorld) : Goodie(IID_HOLY_WATER_GOODIE, startX, startY, 90, 2.0, studentWorld) {
    }
    virtual ~HolyWaterGoodie() {}
    
protected:
    
private:
    virtual void handleOverlap();
    virtual bool isAffectedProjectiles() { return true; }
   
};

class SoulGoodie : public Goodie {
public:
    SoulGoodie(double startX, double startY, StudentWorld* studentWorld) : Goodie(IID_SOUL_GOODIE, startX, startY, 0, 4.0, studentWorld) {
    }
    virtual ~SoulGoodie() {}
    
protected:
    
private:
    virtual void handleOverlap();
    virtual void doSomething();
};

class BorderLine : public Goodie {
public:
    
    BorderLine(int imageID, double startX, double startY, StudentWorld* studentWorld): Goodie(imageID, startX, startY, 0, 2.0, studentWorld) {
    }
    virtual ~BorderLine() {}
    
protected:
    
private:
    virtual void doSomething();
};

class HolyWaterProjectile : public Goodie {
public:
    HolyWaterProjectile(double startX, double startY, int startDirection, StudentWorld* studentWorld) : Goodie(startX, startY, startDirection, studentWorld) {
        m_maxTravDis = 160;
        m_curTravDis = 0;
    }
    virtual ~HolyWaterProjectile() {}
    
protected:
    
private:
    virtual void doSomething();
    int m_maxTravDis;
    int m_curTravDis;
};

class Pedestrian : public Active {
public:
    
    Pedestrian(int imageID, double startX, double startY, int startDirection, double size, double startVertSpeed, double startHorizSpeed, int startHitPoints, StudentWorld* studentWorld) : Active(imageID, startX, startY, startDirection, size, startVertSpeed, startHorizSpeed, startHitPoints, studentWorld) {
        m_movementPlanDis = 0;
    }

    virtual ~Pedestrian() {}
    
protected:
    
    virtual void doSomething();
    
    virtual bool handleOverlap() = 0;
    virtual void receiveDamage(int hitPoints) = 0;
    
    virtual void selectMovementPlan(); //we'll have a basic one used for the peds; zombiecab will overwrite to have its own
    virtual void grunt() {} //optional - ZombiePed only
    virtual bool adjustSpeed() { return false; } //optional - ZombieCab only
 
    int getMovementPlan() { return m_movementPlanDis; }
    void setMovementPlan(int movement) { m_movementPlanDis = movement; }
    
private:
    int m_movementPlanDis;
};

class HumanPed : public Pedestrian {
public:
    HumanPed(double startX, double startY, StudentWorld* studentWorld) : Pedestrian(IID_HUMAN_PED, startX, startY, 0, 2.0, -4.0, 0.0, 0, studentWorld) {
    }
    virtual ~HumanPed() {}

private:
    virtual void receiveDamage(int hitPoints);
    virtual bool handleOverlap();
};

class ZombiePed : public Pedestrian {
public:
    ZombiePed(double startX, double startY, StudentWorld* studentWorld) : Pedestrian(IID_ZOMBIE_PED, startX, startY, 0, 3.0, -4.0, 0.0, 0, studentWorld) {
        m_ticksUntilGrunt = 0;
    }
    virtual ~ZombiePed() {}
    
private:
    virtual void receiveDamage(int hitPoints);
    int m_ticksUntilGrunt;
    
    virtual void grunt();
    virtual bool handleOverlap();

};

class ZombieCab : public Pedestrian {
public:
    ZombieCab(double startX, double startY, double startVertSpeed, StudentWorld* studentWorld) : Pedestrian(IID_ZOMBIE_CAB, startX, startY, 90, 4.0, startVertSpeed, 0.0, 3, studentWorld) {
        m_hasOverlapped = false;
    }
    
    virtual ~ZombieCab() {}
    
private:
    virtual bool handleOverlap();
    virtual void selectMovementPlan();
    virtual bool adjustSpeed();
    
    virtual void receiveDamage(int hitPoints);
    bool m_hasOverlapped;
};

class GhostRacer : public Active { //GhostRacer is derived from Actor
public:
    GhostRacer(StudentWorld *studentWorld) : Active(studentWorld) {
       m_holyWaterUnits = 10;
    }
    virtual ~GhostRacer() {} //virtual functions must be defined (Even if they're empty)
    
    virtual bool isAffectedProjectiles() { return false; }
    virtual void receiveDamage(int damage);
    void addWater(int charge);
    void spin();
    virtual void doSomething();
    int getSprays();
    
private:

    void move();
    
    int m_holyWaterUnits;
};

#endif // ACTOR_H_
