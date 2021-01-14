//
//  testSequence.cpp
//  homework1
//
//  Created by Grace Kwak on 1/14/21.
//

#include "Sequence.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {

    Sequence s;
    
    assert(s.empty()); // - - -
    assert(s.insert(42, 5) == -1); // - - -
    assert(s.insert(42) == 0); // 42 - -
    assert(s.insert(1, 43) == 1); // 42 43 -
    assert(s.insert(0, 41) == 0); // 41 42 43
    assert(s.insert(1, 41) == 1); // 41 41 42 43
    
    assert(s.size() == 4);
    assert(s.empty() == 0);
    
    assert(s.insert(40) == 0); // 40 41 41 42 43
    assert(s.insert(42) == 3); // 40 41 41 42 42 43
    assert(s.insert(43) == 5); // 40 41 41 42 42 43 43

    assert(s.size() == 7);
    assert(s.empty() == 0);

   cout << "Passed all tests" << endl;
}
