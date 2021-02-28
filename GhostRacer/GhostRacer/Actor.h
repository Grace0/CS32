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
    
    //Main functions
    virtual void doSomething() = 0;
    virtual void receiveDamage(int hitPoints) = 0;
    
    //Setters/getters
    void addHealth(int health);
    int getHealth();
    
    //Properties
    virtual bool isAffectedProjectiles() { return true; }
    bool collisionAvoidanceWorthy() { return true; }
    
    virtual ~Active() {}
    
protected:
    
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
    
    //Main functions
    virtual void doSomething();
    virtual void handleOverlap() {};
    
    //Properties
    virtual bool isAffectedProjectiles() { return false; }
    virtual bool collisionAvoidanceWorthy() { return false; }
    
    void receiveDamage(int damage) { setToDead(); }
    
    virtual ~Goodie() {}
    
protected:
    
private:
};

class OilSlick : public Goodie {
public:
    OilSlick(double startX, double startY, StudentWorld* studentWorld) : Goodie(IID_OIL_SLICK, startX, startY, 0, randInt(2,5), studentWorld) {
    }
    virtual ~OilSlick() {}
    virtual void handleOverlap();
    
protected:
    
private:
};

class HealingGoodie : public Goodie {
public:
    HealingGoodie(double startX, double startY, StudentWorld* studentWorld) : Goodie(IID_HEAL_GOODIE, startX, startY, 0, 1.0, studentWorld) {
    }
    virtual ~HealingGoodie() {}
    virtual void handleOverlap();
    
    virtual bool isAffectedProjectiles() { return true; }
    
protected:
    
private:
};

class HolyWaterGoodie : public Goodie {
public:
    HolyWaterGoodie(double startX, double startY, StudentWorld* studentWorld) : Goodie(IID_HOLY_WATER_GOODIE, startX, startY, 90, 2.0, studentWorld) {
    }
    virtual ~HolyWaterGoodie() {}
    
    virtual void handleOverlap();
    virtual bool isAffectedProjectiles() { return true; }
   
protected:
    
private:
};

class SoulGoodie : public Goodie {
public:
    SoulGoodie(double startX, double startY, StudentWorld* studentWorld) : Goodie(IID_SOUL_GOODIE, startX, startY, 0, 4.0, studentWorld) {
    }
    virtual ~SoulGoodie() {}
    virtual void handleOverlap();
    virtual void doSomething();
    
protected:
    
private:
};

class BorderLine : public Goodie {
public:
    
    BorderLine(int imageID, double startX, double startY, StudentWorld* studentWorld): Goodie(imageID, startX, startY, 0, 2.0, studentWorld) {
    }
    virtual ~BorderLine() {}
    virtual void doSomething();
private:
};

class HolyWaterProjectile : public Goodie {
public:
    HolyWaterProjectile(double startX, double startY, int startDirection, StudentWorld* studentWorld) : Goodie(startX, startY, startDirection, studentWorld) {
        m_maxTravDis = 160;
        m_curTravDis = 0;
    }
    virtual ~HolyWaterProjectile() {}
    virtual void doSomething();
private:
    int m_maxTravDis;
    int m_curTravDis;
};


//int imageID, double startX, double startY, int startDirection, double size, int depth, StudentWorld* studentWorld
class Pedestrian : public Active {
public:
    
    Pedestrian(int imageID, double startX, double startY, int startDirection, double size, double startVertSpeed, double startHorizSpeed, int startHitPoints, StudentWorld* studentWorld) : Active(imageID, startX, startY, startDirection, size, startVertSpeed, startHorizSpeed, startHitPoints, studentWorld) {
        m_movementPlanDis = 0;
    //    setVertSpeed(startVertSpeed);
     //   setHorizSpeed(startHorizSpeed);
      //  m_hitPoints = startHitPoints;
    }
    
    virtual void doSomething(); //how does it vary?
    virtual bool handleOverlap() = 0; //varies between Zombie and human and zombiecab
    virtual void receiveDamage(int hitPoints) = 0;
    virtual void selectMovementPlan(); //we'll have a basic one used for the peds; zombiecab will overwrite to have its own
    virtual void grunt() {} //optional - ZombiePed only
    virtual bool adjustSpeed() { return false; } //optional - ZombieCab only
 
  //  int getHitPoints() { return m_hitPoints; }
 //   void setHitPoints(double hitPoints) { m_hitPoints = hitPoints; }
    
    int getMovementPlan() { return m_movementPlanDis; }
    void setMovementPlan(int movement) { m_movementPlanDis = movement; }

    virtual ~Pedestrian() {}
    
private:
    int m_movementPlanDis;
 //   int m_hitPoints;
};

class HumanPed : public Pedestrian {
public:
    HumanPed(double startX, double startY, StudentWorld* studentWorld) : Pedestrian(IID_HUMAN_PED, startX, startY, 0, 2.0, -4.0, 0.0, 0, studentWorld) {
    }
    virtual ~HumanPed() {}
    virtual void receiveDamage(int hitPoints);
    

private:

    virtual bool handleOverlap();
};

class ZombiePed : public Pedestrian {
public:
    ZombiePed(double startX, double startY, StudentWorld* studentWorld) : Pedestrian(IID_ZOMBIE_PED, startX, startY, 0, 3.0, -4.0, 0.0, 0, studentWorld) {
        m_ticksUntilGrunt = 0;
    }
    virtual ~ZombiePed() {}
    virtual void receiveDamage(int hitPoints);
    
private:
    
    int m_ticksUntilGrunt;
    
    virtual void grunt();
    virtual bool handleOverlap();

};

class ZombieCab : public Pedestrian {
public://int imageID, double startX, double startY, int startDirection, double size, int depth, double startVertSpeed, double startHorizSpeed, StudentWorld* studentWorld
    //int imageID, double startX, double startY, int startDirection, double size, double startVertSpeed, double startHorizSpeed, int startHitPoints, StudentWorld* studentWorld
    ZombieCab(double startX, double startY, double startVertSpeed, StudentWorld* studentWorld) : Pedestrian(IID_ZOMBIE_CAB, startX, startY, 90, 4.0, startVertSpeed, 0.0, 3, studentWorld) {
        m_hasOverlapped = false;
    }
    
   // virtual void doSomething(); //doesn't quite just use pedestrian's doSomething
    virtual bool handleOverlap();
    virtual void selectMovementPlan();
    virtual bool adjustSpeed();
    
    virtual void receiveDamage(int hitPoints);
    virtual ~ZombieCab() {}
    
private:
    bool m_hasOverlapped;
};

class GhostRacer : public Active { //GhostRacer is derived from Actor
public:
    GhostRacer(StudentWorld *studentWorld) : Active(studentWorld) {
       m_holyWaterUnits = 10;
    }
    virtual ~GhostRacer() {} //virtual functions must be defined (Even if they're empty)
    
    virtual void doSomething();
    virtual void receiveDamage(int damage);
    
    void spin();
    void addWater(int charge);
    int getSprays();
    void move();
    
    virtual bool isAffectedProjectiles() { return false; }
    
private:
    int m_holyWaterUnits;
};

#endif // ACTOR_H_
