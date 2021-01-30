#include <iostream>
#include <cassert>
using namespace std;

class Num
{
  public:
    Num(int i) : m_i(i) {}
    int geti() const { return m_i; }
  private:
    int m_i;
};

class Blah
{
  public:
    Blah(int i);
    ~Blah();
    Blah(const Blah& other);
  private:
    Num* m_num;
    int m_ii;
    int* m_eyes;
};

Blah::Blah(int i)
{
  m_num = new Num(i);
  m_ii = 2 * i;
  m_eyes = &m_ii;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE DESTRUCTOR AND COPY CONSTRUCTOR
// IMPLEMENTATIONS

Blah::~Blah() {
    delete m_num;
}

Blah::Blah(const Blah& other) {
    m_num = new Num(other.m_num->geti());
    m_ii = 2 * other.m_num->geti();
    m_eyes = &m_ii;

}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE DESTRUCTOR AND COPY CONSTRUCTOR
// IMPLEMENTATIONS

void test()
{
  Blah b1(3);
  Blah b2(b1);
}

int main()
{
  test();
  cout << "All tests succeeded" << endl;
}

//
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//class StringList
//{
//  public:
//    StringList();
//    // You may declare other member functions for your test code to call
//    void insert(char value);
//    void eraseEvens();
//  private:
//    struct Node
//    {
//      char  value;
//      Node* next;
//    };
//    Node* head;  // points to first Node in the list
//};
//
//StringList::StringList()
//{
//  head = nullptr;
//}
//
//void StringList::insert(char value) {
//    Node *newNode = new Node;
//    newNode->value = value;
//    newNode->next = nullptr;
//
//    if (head == nullptr) {
//        head = newNode;
//        return;
//    }
//
//    Node *ptr = head;
//    while (ptr->next != nullptr) {
//        ptr = ptr->next;
//    }
//    ptr->next = newNode;
//}
//// You may implement other member functions here for test purposes,
//// but you will not turn them in as part of your submission.
//
//// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
//// COMMENT AFTER THE END OF THE eraseEvens IMPLEMENTATION
//
//void StringList::eraseEvens() {
//
//    Node *ptr1 = head;
//    while (ptr1 != nullptr) {
//        Node *ptr2 = ptr1->next;
//        if (ptr2 != nullptr) {
//            ptr1->next = ptr2->next;
//            delete ptr2;
//        }
//        ptr1 = ptr1->next;
//    }
//}
//
//// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
//// COMMENT BEFORE THE START OF THE eraseEvens IMPLEMENTATION
//
//int main()
//{
//
//    StringList s;
//    s.insert('s');
//    s.insert('q');
//    s.insert('u');
//    s.insert('i');
//    s.insert('n');
//    s.insert('t');
//
//    s.eraseEvens();
//  // You may put some code here for test purposes
//  cout << "All tests succeeded" << endl;
//}
