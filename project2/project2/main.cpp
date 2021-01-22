//
//  main.cpp
//  project2
//
//  Created by Grace Kwak on 1/20/21.
//

#include <iostream>
#include <cassert>

#include "Sequence.h"
using namespace std;

int main() {
    
    Sequence s;
    
    assert(s.empty() == 1);
    assert(s.size() == 0);
    
    s.insert(0, 1);
    
    cerr << "Hello, World!\n";
    return 0;
}
