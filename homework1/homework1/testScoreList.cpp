//
//  testScoreList.cpp
//  homework1
//
//  Created by Grace Kwak on 1/15/21.
//

#include "ScoreList.h"
#include <cassert>
#include <iostream>
using namespace std;

int main() {

    ScoreList scores;

    assert(scores.add(88) == 1); //88
    assert(scores.add(-9) == 0);
    assert(scores.add(300) == 0);
    assert(scores.add(0) == 1); // 0 88

    assert(scores.remove(88) == 1); // 0
    assert(scores.remove(0) == 1); // -

    assert(scores.maximum() == NO_SCORE);
    assert(scores.minimum() == NO_SCORE);

    assert(scores.add(88) == 1); //88
    assert(scores.maximum() == 88);
    assert(scores.minimum() == 88);

    assert(scores.add(77) == 1);
    assert(scores.maximum() == 88);
    assert(scores.minimum() == 77);

    cerr << "Passed all tests" << endl;
}
