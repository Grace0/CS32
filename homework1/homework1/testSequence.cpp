#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
//    Sequence s;
//
//    assert(s.empty()); // - - -
//    assert(s.insert(42, "five") == -1); // - - -
//    assert(s.insert("fourtytwo") == 0); // "fourtytwo" - -
//    assert(s.insert(1, "fourtythree") == 1); // "fourtytwo" "fourtythree" -
//    assert(s.insert(0, "fourtyone") == 0); // "fourtyone" "fourtytwo" "fourtythree"
//    assert(s.insert(1, "fourtyone") == 1); // "fourtyone" "fourtyone" "fourtytwo" "fourtythree"
//
//    assert(s.size() == 4);
//    assert(s.empty() == 0);
//
//    assert(s.insert("fourty") == 0); // 40 "fourtyone" "fourtyone" "fourtytwo" "fourtythree"
//    assert(s.insert("fourtytwo") == 3); // 40 "fourtyone" "fourtyone" "fourtytwo" "fourtytwo" "fourtythree"
//    assert(s.insert("fourtythree") == 3); // 40 "fourtyone" "fourtyone" "fourtytwo" "fourtytwo" "fourtythree" "fourtythree"
////
//    assert(s.size() == 7);
//    assert(s.empty() == 0);
//
//    assert(s.erase(4) == true); // 40 "fourtyone" "fourtyone" "fourtytwo" "fourtythree" "fourtythree"
//    assert(s.erase(0) == true); // "fourtyone" "fourtyone" "fourtytwo" "fourtythree" "fourtythree"
//    assert(s.erase(-43) == false);
//    assert(s.erase(s.size()-1) == true); // "fourtyone" "fourtyone" "fourtytwo" "fourtythree"
//
//    assert(s.size() == 4);
//
//    assert(s.remove("eightyeight") == 0); // "fourtyone" "fourtyone" "fourtytwo" "fourtythree"
//    assert(s.remove("fourtyone") == 2); // "fourtytwo" "fourtythree"
//    assert(s.remove("fourtythree") == 1); // "fourtytwo"
//
//    assert(s.size() == 1);
//
//    std::string p = "nineninenine";
//    assert(s.get(4, p) == false);
//    assert(p == "nineninenine");
//    assert(s.get(0, p) == true);
//    assert(p == "fourtytwo");
//    assert(s.get(-8, p) == false);
//    assert(p == "fourtytwo");
//
//    std::string q = "fivefivefive";
//    assert(s.set(0, q) == true);
//    assert(s.set(-9, q) == false);
//    assert(s.set(1, q) == false);
//
//    assert(s.find("fivefivefive") == 0);
//    assert(s.find("zero") == -1);
//
//    assert(s.insert("a") == 0); //40 555
//    assert(s.find("a") == 0);
//    assert(s.insert("a") == 0); // 40 40 555
//    assert(s.find("a") == 0);

    Sequence s1;
     s1.insert(0, "paratha");
     s1.insert(0, "focaccia");
     Sequence s2;
     s2.insert(0, "roti");
     s1.swap(s2);
     assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
                 s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);

    Sequence s;
    s.insert(0, "a");
    s.insert(1, "b");
    s.insert(2, "c");
    s.insert(3, "b");
    s.insert(4, "e");
    assert(s.remove("b") == 2);
    assert(s.size() == 3);
    string x;
    assert(s.get(0, x)  &&  x == "a");
    assert(s.get(1, x)  &&  x == "c");
    assert(s.get(2, x)  &&  x == "e");

    Sequence s3;
       s3.insert(0, "dosa");
       s3.insert(1, "pita");
       s3.insert(2, "");
       s3.insert(3, "matzo");
       assert(s3.find("") == 2);
       s3.remove("dosa");
       assert(s3.size() == 3  &&  s3.find("pita") == 0  &&  s3.find("") == 1  &&
                   s3.find("matzo") == 2);


//
//    Sequence t;
//    assert(t.empty()); // - - -
//    assert(t.insert("fourtytwo", 5) == -1); // - - -
//    assert(t.insert("fourtytwo") == 0); // "fourtytwo" - -
//    assert(t.insert(1, "fourtythree") == 1); // "fourtytwo" "fourtythree" -
//    assert(t.insert(0, "fourtyone") == 0); // "fourtyone" "fourtytwo" "fourtythree"
//    assert(t.insert(1, "fourtyone") == 1); // "fourtyone" "fourtyone" "fourtytwo" "fourtythree"
//
//    t.swap(s);
//    assert(s.size() == 4);
//    assert(t.size() == 3);
//
//    s.swap(t);
//    assert(s.size() == 3);
//    assert(t.size() == 4);
//
//    Sequence u = t;
//    assert(u.size() == 4);
//
//    Sequence v = s;
//    assert(v.size() == 3);

    cerr << "Passed all tests" << endl;
}
