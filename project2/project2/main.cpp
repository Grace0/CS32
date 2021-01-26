////
////  main.cpp
////  project2
////
////  Created by Grace Kwak on 1/20/21.
////
//
//#include <iostream>
//#include <cassert>
//
//#include "Sequence.h"
//using namespace std;
//
//int main() {
//
//    Sequence s;
//    Sequence t;
//
//    s.insert(0,30);
//    s.insert(1,21);
//    s.insert(2,63);
//    s.insert(3,42);
//    s.insert(4,17);
//    s.insert(5,63);
//    s.insert(6,17);
//    s.insert(7,29);
//    s.insert(8,8);
//    s.insert(9,32);
//
//    t.insert(0,63);
//    t.insert(1,17);
//    t.insert(2,29);
//
//    assert(subsequence(s, t) == 5); //one possible k exists
//    assert(subsequence(t, s) == -1); //seq1.size < seq2.size
//
//    assert(subsequence(t, t) == 0); //subsequence of itself
//
//    Sequence u;
//    u.insert(0,63);
//    u.insert(1,17);
//    u.insert(2,29);
//    u.insert(3,42);
//    u.insert(4,17);
//    u.insert(5,63);
//    u.insert(6,17);
//    u.insert(7,29);
//    assert(subsequence(u, t) == 0); //subsequence() must return the *smallest* such k
//
//    Sequence v;
//    u.insert(0,6);
//    u.insert(1,1);
//    u.insert(2,2);
//    u.insert(3,4);
//    u.insert(4,1);
//    u.insert(5,6);
//    u.insert(6,1);
//    u.insert(7,2);
//    assert(subsequence(v, t) == -1); //no such k exists
//
//    Sequence p;
//    p.insert(0,30);
//    p.insert(1,21);
//    p.insert(2,63);
//    p.insert(3,42);
//
//    Sequence q;
//    q.insert(0,42);
//    q.insert(1,63);
//    q.insert(2,84);
//    q.insert(3,19);
//
//    Sequence r;
//    r.insert(0,3131);
//    r.insert(1,3107);
//
//    //if seq1 is empty
//    //if seq2 is empty
//    Sequence w;
//    Sequence x;
//    assert(subsequence(w, x) == -1);
//    assert(subsequence(x, w) == -1);
//
//    Sequence y;
//    interleave(w, x, y);
//    assert(y.empty() == true); //both seq1 and seq2 empty
//
//    Sequence z;
//    interleave(w, t, z);
//    assert(z.empty() == false); //seq1 empty, seq2 non-empty
//
//    Sequence aa;
//    interleave(t, w, aa);
//    assert(aa.empty() == false); //seq1 non-empty, seq2 empty
//    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    Sequence ab; // m = n
//    interleave(p, q, ab);
//
//    Sequence ac; // n = m
//    interleave(q, p, ac);
//
//    Sequence ad; // m > n
//    interleave(q, r, ad);
//
//    Sequence ae; // m < n
//    interleave(r, q, ae);
//
//    interleave(r, r, r); //seq1, seq2, result refer to the same Sequence
//
//    Sequence qa;
//    qa.insert(0,42);
//    qa.insert(1,63);
//    qa.insert(2,84);
//    qa.insert(3,19);
//
//    Sequence ra;
//    ra.insert(0,3131);
//    ra.insert(1,3107);
//    interleave(ra, qa, ra); //seq1 and result refer to the same Sequence
//
//
//    Sequence rb;
//    rb.insert(0,3131);
//    rb.insert(1,3107);
//    interleave(qa, rb, rb); //seq2 and result refer to the same Sequence
//
//    interleave(qa, qa, ra); //seq1 and seq2 refer to the same Sequence
//
//    Sequence af;
//    Sequence ag;
//    interleave(af, qa, ra); //seq1 is empty
//    interleave(qa, af, ra); //seq2 is empty
//    interleave(af, ag, ra); //both seq1 and seq2 are empty
//
//    cerr << "Passed all tests." << endl;
//    return 0;
//}

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;



int main()
{
//    
//    Sequence s, t;
//    ItemType a = 999;
//    assert(s.insert(-1,1) == -1); //Insertion in invalid pos returns -1, no change to the sequence
//    assert(s.size() == 0); //Empty sequence has length zero
//    assert(s.empty()); //Sequence should be empty by default
//    assert(s.erase(0) == false); //Can’t erase from empty sequence
//    assert(s.remove(2) == 0); //Return 0 because no removes
//    assert(s.get(0, a) == false); //Invalid position, return false
//    assert(a == 999); //a should be unchanged by get
//    assert(s.set(0, a) == false); //Invalid position, return false
//    assert(s.find(2) == -1); //No elements, return -1
//    s.swap(t);
//    assert(s.empty()); //Check that swapping doesn’t change anything
//    assert(s.insert(0) == 0); assert(s.insert(2) == 1); //Ensure that insertion by value returns correct index
//    assert(s.size() == 2); //Check to see if size increases after insertion
//    assert(s.empty() == false); //Check that sequence is no longer empty
//    assert(s.insert(1) == 1); //Inserts into correct position at index 1
//    assert(s.insert(0, 10) == 0); //Should insert at position zero and shift all terms up by 1
//    assert(s.insert(4, 15) == 4); //Insertion at the end of sequence is valid
//    assert(s.get(4, a)); //True because there is data at index 4
//    assert(a == 15); //get succeeded, so 15 is stored in a
//    assert(s.set(4, 20)); //True because index 4 is valid
//    assert(s.set(67, 20) == false); //Since 67 is an invalid index, return false and leave sequence unchanged
//    assert(s.size() == 5); //verify that sequence is unchanged
//    assert(s.erase(0)); //Return true since there is an item at index 0
//    s.get(0, a);
//    assert(a == 0); //a now stores 0 because 10 was removed and all elements were shifted down
//    s.insert(1, 1);
//    assert(s.find(1) == 1); //Find searches for first index, returning index 1 even though there is a 1 at index 2
//    assert(s.remove(1) == 2); //remove should erase both occurrences of 1
//    assert(s.size() == 3); //Verify that size is now smaller after removal
//    s.swap(t);
//    assert(t.size() == 3 && s.size() == 0); //Verify that swapping with an empty sequence works
//    s.insert(1);
//    s.swap(t);
//    assert(t.size() == 1 && s.size() == 3); //After swapping back, s should have its original 3 elements and t should have 1
//    Sequence u(s);
//    u.insert(3, 9);
//    assert(u.size() == 4 && s.size() == 3); //Copy constructor does not link the two objects
//    u = t;
//    u.insert(1, 6);
//    assert(u.size() == 2 && t.size() == 1); //Assignment operator does not link the two objects
//    
//        Sequence v;
//        v.insert(0,1);
//        v.insert(1,2);
//        v.insert(2,3);
//        v.insert(3,2);
//        v.insert(4,3);
//        v.insert(5,4);
//    
//    Sequence w;
//    w.insert(0,2);
//    w.insert(1,3);
//    w.insert(2,4);
//    
//    Sequence p;
//    p.insert(2);
//
// //   Sequence v containing [1,2,3,2,3,4]
//  //  Sequence w containing [2,3,4]
// //   Sequence p containing [2]
//    Sequence x, y, z;
//    assert(subsequence(v, w) == 3); //Subsequence starts at 3, 2,3 does not make a subsequence
//    assert(subsequence(v, p) == 1); //Returns first occurrence, ignoring the second 2
//    assert(subsequence(w, v) == -1); //-1 bc v is larger than w
//    assert(subsequence(v, v) == 0); //A sequence is its own subsequence
//    assert(subsequence(v, x) == -1 && subsequence(x, v) == -1 && subsequence(x, y) == -1); //Returns -1 if one or more of the sequences are empty
//    interleave(w, v, x);
//   // x.dump(); //Should contain alternating w then v until w runs out, then all v
//    interleave(v, w, x);
//  //  x.dump(); //Should contain alternating v then w until w runs out, then all v
//    interleave(y, z, x);
// //   x.dump(); //x is now empty and should not print anything
//    interleave(v, x, x);
// //   x.dump(); //x now is identical to v because there were no x terms to insert
//    interleave(v, v, v);
//  //  v.dump(); //v now has each term repeated twice, make sure there are no aliasing issues
//
//    cout << "Passed all tests" << endl;
}
