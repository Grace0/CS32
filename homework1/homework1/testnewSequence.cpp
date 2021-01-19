#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;
//
//int main()
//{
//    Sequence a(1000);   // a can hold at most 1000 items
//    Sequence b(5);      // b can hold at most 5 items
//    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
//    unsigned long v = 99;
//
//      // No failures inserting 5 items into b
//    for (int k = 0; k < 5; k++)
//        assert(b.insert(v) != -1);
//
//      // Failure if we try to insert a sixth item into b
//    assert(b.insert(v) == -1);
//
//      // When two Sequences' contents are swapped, their capacities are
//      // swapped as well:
//    a.swap(b);
//    assert(a.insert(v) == -1  &&  b.insert(v) != -1);
//    
//    a.swap(a);
//    a.swap(b);
//    assert(a.insert(v) != -1  &&  b.insert(v) == -1);
//    
//  //  assert(a.size() ==
////
////    Sequence a(1000);   // a can hold at most 1000 items
////    Sequence b(5);      // b can hold at most 5 items
////    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
////    unsigned long v = 99;
////
////    // No failures inserting 5 items into b
////    for (int k = 0; k < 5; k++)
////      assert(b.insert(v) != -1);
////
////    for (int k = 0; k < 1000; k++)
////      assert(a.insert(v) != -1);
////
////    for (int k = 0; k < 150; k++)
////      assert(c.insert(v) != -1);
////
////    Sequence d = c;
////    Sequence e = d;
////
////    Sequence f(a);
////    Sequence g(b);
////
////    // Failure if we try to insert a sixth item into b
////    assert(b.insert(v) == -1);
////    assert(a.insert(v) == -1);
////    assert(c.insert(v) == -1);
////    assert(d.insert(v) == -1);
////    assert(e.insert(v) == -1);
////    assert(f.insert(v) == -1);
////    assert(g.insert(v) == -1);
////
////    d = a;
////    c = g;
////    e = e;
////
////    //        // When two Sequences' contents are swapped, their capacities are
////    //        // swapped as well:
////
////    Sequence h(1000);   // a can hold at most 1000 items
////    Sequence i(5);      // b can hold at most 5 items
////          i.swap(h);
////          assert(h.insert(v) == -1  &&  i.insert(v) != -1);
//
//    cerr << "Passed all tests" << endl;
//}
