#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h" //actor->anything is used in function implementations
#include <string>
using namespace std;

const int LEFT_EDGE = ROAD_CENTER-ROAD_WIDTH/2;
const int RIGHT_EDGE = ROAD_CENTER+ROAD_WIDTH/2;

GameWorld* createStudentWorld(string assetPath) //called in main.cpp
{
	return new StudentWorld(assetPath); //returning a pointer to an object of itself?
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_ghostRacer = nullptr;
    m_lastWhite = 0;
    m_playerPoints = 0;
    m_numSaved = 0;
    m_bonusPoints = 5000;
}

int StudentWorld::init()
{
    //yellow border lines //StudentWorld can't have a data member that's a pointer to a single border line object
    for (int n = 0; n < VIEW_HEIGHT/SPRITE_HEIGHT; n++) {
        m_actorVec.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE, n * SPRITE_HEIGHT, this));
        m_actorVec.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, n * SPRITE_HEIGHT, this));
    }
    //white border lines
    for (int m = 0; m < VIEW_HEIGHT/(4*SPRITE_HEIGHT); m++) {
        m_actorVec.push_back(new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3, m * 4*SPRITE_HEIGHT, this));
        m_actorVec.push_back(new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3, m * 4*SPRITE_HEIGHT, this));
        m_lastWhite = m_actorVec[m_actorVec.size()-1]->getY();
    }
    
    m_ghostRacer = new GhostRacer(this);
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    
    if (m_bonusPoints > 0) m_bonusPoints--;
    m_lastWhite -= (4 + m_ghostRacer->getVertSpeed());

    for (int i = 0; i < m_actorVec.size(); i++) {
        if (m_actorVec[i]->isAlive()) {
            m_actorVec[i]->doSomething();
            if (!m_ghostRacer->isAlive()) return GWSTATUS_PLAYER_DIED;
        }
    }

    m_ghostRacer->doSomething();
    if (!m_ghostRacer->isAlive()) return GWSTATUS_PLAYER_DIED;
    
    if (m_numSaved == (2 * getLevel() + 5)) {
        addPoints(m_bonusPoints);
        m_bonusPoints = 5000; //reset
        return GWSTATUS_FINISHED_LEVEL;
    }

    removeDeadActors();

    addNewActors();

    updateDisplayText();
//    Update display text // update the score/lives/level text at screen top
//     // the player hasn’t completed the current level and hasn’t died, so
//     // continue playing the current level

    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_ghostRacer;
    
    for (std::vector<Actor*>::iterator it = m_actorVec.begin(); it != m_actorVec.end(); ) {
        delete *it; // delete what "it" points to
        it = m_actorVec.erase(it); //"it" now points to the next element of the vector (unless it points to the end)
    }
}

StudentWorld::~StudentWorld() {
    cleanUp();
}

void StudentWorld::removeDeadActors() {
    for (std::vector<Actor*>::iterator it = m_actorVec.begin(); it != m_actorVec.end(); ) {
        if (!(*it)->isAlive()) {
            delete *it; //free the memory
            it = m_actorVec.erase(it); //remove from the container
        } else { //increment "it"
            it++;
        }
    }
}
void StudentWorld::addNewActors() {
   
    int level = getLevel();
    
    //Borderlines
    double new_border_y = VIEW_HEIGHT-SPRITE_HEIGHT;
    double delta_y = new_border_y - m_lastWhite;
    
    if (delta_y >= SPRITE_HEIGHT) {
        m_actorVec.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE, new_border_y, this));
        m_actorVec.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, new_border_y, this));
        
    }
    
    if (delta_y >= 4*SPRITE_HEIGHT) {
        m_actorVec.push_back(new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3, new_border_y, this));
        m_actorVec.push_back(new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3, new_border_y, this));
        m_lastWhite = m_actorVec[m_actorVec.size()-1]->getY();
    }
    
    //Zombie Peds
    int chanceZombiePed = max(100 - level * 10, 20);
    if (randInt(0, chanceZombiePed-1) == 0) {
        m_actorVec.push_back(new ZombiePed(randInt(0, VIEW_WIDTH-1), VIEW_HEIGHT-1, this));
    }
    
    //Human Peds
    int chanceHumanPed = max(200 - level * 10, 30);
    if (randInt(0, chanceHumanPed-1) == 0) {
        m_actorVec.push_back(new HumanPed(randInt(0, VIEW_WIDTH-1), VIEW_HEIGHT-1, this));
    }
    
    //Oil Slick
    int chanceOilSlick = max(150 - level * 10, 40);
    if (randInt(0, chanceOilSlick-1) == 0) {
        m_actorVec.push_back(new OilSlick(randInt(0, VIEW_WIDTH-1), VIEW_HEIGHT-1, this));
    }
    
}

void StudentWorld::updateDisplayText() {
    string text = "Score: " + to_string(getScore()) + "  Lvl: " + to_string(getLevel()) + "  Souls2Save: " + to_string(getSouls2Save()) + "  Lives: " + to_string(getLives()) + "  Health: " + to_string(getHealth()) + "  Sprays: " + to_string(getSprays()) + "  Bonus: " + to_string(getBonus()); //stringstream?
    setGameStatText(text);
}

Actor* StudentWorld::closestInLane(int laneNum, double y, bool inFront) {
    
    Actor* potentialClosest = nullptr;
    
//    for (int i = 0; i < m_actorVec.size(); i++) {
//        if (m_actorVec[i]->getLaneNum() == laneNum) {
//            if ((m_actorVec[i]->getY() > y) && (potentialClosest->getY() > m_actorVec[i]->getY())) {
//                potentialClosest = m_actorVec[i];
//            }
//
//        }
//    }
    
    return potentialClosest; //no other actors in the lane
}

void StudentWorld::addPoints(int numPoints) { m_playerPoints += numPoints; }

GhostRacer* StudentWorld::getGhostRacer() { return m_ghostRacer; }

void StudentWorld::incNumSaved() { m_numSaved++; }

int StudentWorld::getScore() {
    return m_playerPoints;
}

int StudentWorld::getHealth() {
    return getGhostRacer()->getHealth();
}

int StudentWorld::getSouls2Save() {
    return (getLevel() * 2 + 5) - m_numSaved; //I think?
}

int StudentWorld::getSprays() {
    return getGhostRacer()->getSprays();
}

int StudentWorld::getBonus() {
    return m_bonusPoints;
}

//takes a pointer to a projectile
//loops through all the Actors to see if there's one that isAffectedByProjectiles and overlaps with the projectile at hand
//returns the first Actor it finds that meets those req's; if none found, returns nullptr
Actor* StudentWorld::getProjectileOverlap(HolyWaterProjectile* proj) {
    for (int i = 0; i < m_actorVec.size(); i++) {
        if (m_actorVec[i]->isAffectedProjectiles() && m_actorVec[i]->doOverlap(proj)) {
            return m_actorVec[i];
        }
    }
    
    return nullptr;
}

void StudentWorld::addHealingGoodie(double startX, double startY) {
    m_actorVec.push_back(new HealingGoodie(startX, startY, this));
}

void StudentWorld::addOilSlick(double startX, double startY) {
    m_actorVec.push_back(new OilSlick(startX, startY, this));
}
