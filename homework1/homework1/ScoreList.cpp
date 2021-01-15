#include "ScoreList.h"

ScoreList::ScoreList() {
    
}

bool ScoreList::add(unsigned long score) {
    if (score < 0 || score > 100 || m_sequence.size() > DEFAULT_MAX_ITEMS) return false;
    
    m_sequence.insert(score);
    return true;
}

bool ScoreList::remove(unsigned long score) {
    int firstInstancePos = m_sequence.find(score);
    
    if (firstInstancePos != -1) {
        m_sequence.erase(firstInstancePos);
        return true;
    }
    
    return false;
}
 
int ScoreList::size() const {
    return m_sequence.size();
}

unsigned long ScoreList::minimum() const {
    if (size() == 0) return NO_SCORE;
    
    unsigned long firstScore;
    m_sequence.get(0, firstScore);
    return firstScore;
}

unsigned long ScoreList::maximum() const {
    if (size() == 0) return NO_SCORE;
    
    unsigned long lastScore;
    m_sequence.get(size()-1, lastScore);
    return lastScore;
    
}


