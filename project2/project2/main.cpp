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
    Sequence e;
    
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
    
    assert(e.erase(0) == 0); //trying to erase from an empty list
    assert(s.erase(-13) == 0); //erase invalid pos
    assert(s.erase(988) == 0); //erase invalid pos
    
    assert(s.erase(0) == 1); //erase first Node
    assert(s.erase(1) == 1); //erase middle Node
    assert(s.erase(2) == 1); //erase last Node
    assert(s.size() == 4);
    
    Sequence t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    
 //   Sequence u = t;
 //   Sequence v(u);
    
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
    assert(e.get(34, g) == 0); //get from an empty list
    
    t.set(0, 10); //set first Node val
    t.set(1, 20); //set middle Node val
    t.set(2, 30); //set middle Node val
    t.set(3, 40); //set last Node val
    assert(t.get(0, g) == 1);
    assert(g == 10);
    assert(t.get(1, g) == 1);
    assert(g == 20);
    assert(t.get(2, g) == 1);
    assert(g == 30);
    assert(t.get(3, g) == 1);
    assert(g == 40);
    
    assert(t.set(-249, 0) == 0); //set invalid pos
    assert(t.set(9393, 38) == 0); //set invalid pos
    
    assert(t.find(0) == -1); //val not found
    assert(t.find(10) == 0); //val found at beginning
    assert(t.find(20) == 1); //val found in middle
    assert(t.find(30) == 2); //val found in middle
    assert(t.find(40) == 3); //val found at end
    
    assert(t.remove(348) == 0); //removes no values
    assert(t.remove(10) == 1); //removes one value
    t.insert(20);
    assert(t.remove(20) == 2); //removes multiple values
    
    t.swap(s); //swap two non-empty LL
    assert(s.size() == 2);
    assert(t.size() == 4);
    s.swap(t);
    assert(s.size() == 4);
    assert(t.size() == 2);
    
    e.swap(t); //swap one empty LL with one non-empty LL
    assert(e.empty() == 0);
    assert(t.empty() == 1);
    t.swap(e);
    assert(e.empty() == 1);
    assert(t.empty() == 0);
    
    Sequence e2;
    e.swap(e2); //swap two empty LL
    assert(e.empty() == 1);
    assert(e2.empty() == 1); //test empty when empty
    
    Sequence r = t; //copy constructor on a non-empty LL
    Sequence w = e; //copy constructor on an empty LL
    
    r = w; //call assignment operator to assign a non-empty LL to an empty LL
    e = t; //call assignment operator to assign an empty LL to a non-empty LL
    
    cerr << "Passed all tests." << endl;
    return 0;
}
