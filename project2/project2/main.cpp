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
    
    assert(s.empty() == 1); //test empty when empty
    assert(s.size() == 0); //test size
    
    assert(s.insert(0, 1) == 0); //insert at beginning of sequence
    assert(s.empty() == 0); //test empty when not empty
    
    assert(s.insert(1, 3) == 1); //insert at end of sequence
    assert(s.insert(1, 2) == 1); //insert in middle of sequence
    assert(s.insert(-1, 879) == -1); //pos out of bounds
    assert(s.insert(907, 879) == -1); //pos out of bounds
    assert(s.size() == 3); //test size
    ///1 2 3
    
    assert(s.insert(4) == 3); //insert value greater than all current node values
    assert(s.insert(4) == 3); //insert value greater than or equal to all current node values
    //1 2 3 4 4
    assert(s.size() == 5);
    assert(s.insert(3) == 2); //insert a value less than some nodes but greater than other nodes
    assert(s.insert(0) == 0); //insert a value less than all other nodes
    
    assert(s.erase(-13) == 0); //erase invalid pos
    assert(s.erase(988) == 0); //erase invalid pos
    
    assert(s.erase(0) == 1); //erase first Node
    assert(s.erase(1) == 1); //erase middle Node
    assert(s.erase(2) == 1); //erase last Node
    assert(s.size() == 4);
    
    //Copy constructor
    
    Sequence t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    
    unsigned long g = 0;
    assert(t.get(0, g) == 1); //get first val
    assert(g == 1);
    assert(t.get(1, g) == 1);  //get middle val
    assert(g == 2);
    assert(t.get(2, g) == 1);  //get middle val
    assert(g == 3);
    assert(t.get(3, g) == 1);  //get last val
    assert(g == 4);
    
    assert(t.get(-88, g) == 0); //get invalid pos
    assert(t.get(993, g) == 0); //get invalid pos
    
    cerr << "Passed all tests." << endl;
    return 0;
}
