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
    Sequence t;
    
    s.insert(0,30);
    s.insert(1,21);
    s.insert(2,63);
    s.insert(3,42);
    s.insert(4,17);
    s.insert(5,63);
    s.insert(6,17);
    s.insert(7,29);
    s.insert(8,8);
    s.insert(9,32);
    
    t.insert(0,63);
    t.insert(1,17);
    t.insert(2,29);

    assert(subsequence(s, t) == 5); //one possible k exists
    assert(subsequence(t, s) == -1); //seq1.size < seq2.size
    
    Sequence u;
    u.insert(0,63);
    u.insert(1,17);
    u.insert(2,29);
    u.insert(3,42);
    u.insert(4,17);
    u.insert(5,63);
    u.insert(6,17);
    u.insert(7,29);
    assert(subsequence(u, t) == 0); //subsequence() must return the *smallest* such k
    
    Sequence v;
    u.insert(0,6);
    u.insert(1,1);
    u.insert(2,2);
    u.insert(3,4);
    u.insert(4,1);
    u.insert(5,6);
    u.insert(6,1);
    u.insert(7,2);
    assert(subsequence(v, t) == -1); //no such k exists
    
    //if seq1 is empty
    //if seq2 is empty
    Sequence w;
    Sequence x;
    assert(subsequence(w, x) == -1);
    assert(subsequence(x, w) == -1);
    
    cerr << "Passed all tests." << endl;
    return 0;
}
