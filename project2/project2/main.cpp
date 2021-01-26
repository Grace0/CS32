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
    
    assert(subsequence(t, t) == 0); //subsequence of itself
    
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
    
    Sequence p;
    p.insert(0,30);
    p.insert(1,21);
    p.insert(2,63);
    p.insert(3,42);

    Sequence q;
    q.insert(0,42);
    q.insert(1,63);
    q.insert(2,84);
    q.insert(3,19);
    
    Sequence r;
    r.insert(0,3131);
    r.insert(1,3107);
    
    //if seq1 is empty
    //if seq2 is empty
    Sequence w;
    Sequence x;
    assert(subsequence(w, x) == -1);
    assert(subsequence(x, w) == -1);
    
    Sequence y;
    interleave(w, x, y);
    assert(y.empty() == true); //both seq1 and seq2 empty
    
    Sequence z;
    interleave(w, t, z);
    assert(z.empty() == false); //seq1 empty, seq2 non-empty
   
    Sequence aa;
    interleave(t, w, aa);
    assert(aa.empty() == false); //seq1 non-empty, seq2 empty
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Sequence ab; // m = n
    interleave(p, q, ab);
    
    Sequence ac; // n = m
    interleave(q, p, ac);
    
    Sequence ad; // m > n
    interleave(q, r, ad);
    
    Sequence ae; // m < n
    interleave(r, q, ae);
    
    interleave(r, r, r); //seq1, seq2, result refer to the same Sequence
    
    Sequence qa;
    qa.insert(0,42);
    qa.insert(1,63);
    qa.insert(2,84);
    qa.insert(3,19);
    
    Sequence ra;
    ra.insert(0,3131);
    ra.insert(1,3107);
    interleave(ra, qa, ra); //seq1 and result refer to the same Sequence
    
    
    Sequence rb;
    rb.insert(0,3131);
    rb.insert(1,3107);
    interleave(qa, rb, rb); //seq2 and result refer to the same Sequence
    
    interleave(qa, qa, ra); //seq1 and seq2 refer to the same Sequence
    
    cerr << "Passed all tests." << endl;
    return 0;
}
