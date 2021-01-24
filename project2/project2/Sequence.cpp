// Sequence.cpp

#include "Sequence.h"

Sequence::Sequence()
 : m_size(0)
{
    dummy = new Node;
    dummy->next = dummy;
    dummy->prev = dummy;

}

Sequence::~Sequence() {
    
    Node *deleteFirst = dummy;
    
    for (int i = 0; i < m_size; i++) {
        Node *deleteNext = deleteFirst->next;
        delete deleteFirst;
        deleteFirst = deleteNext;
    }
}

Sequence::Sequence(const Sequence& src) {
    m_size = src.m_size;
    
    dummy = new Node;
    dummy->next = dummy;
    dummy->prev = dummy;
    
    Node *ptr = src.dummy;
    
    for (int i = 0; i < m_size; i++) {
        ptr = ptr->next;
        insert(i, ptr->value);
    }

}

Sequence& Sequence::operator=(const Sequence& src) {
    
    Sequence temp = src;
    
    if (this != &src) {
        swap(temp);
    }
    return *this;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0  ||  pos > size())
    return -1;
    
    Node *traverse = dummy; //traverse points to the Node right before
    for (int i = 0; i < pos; i++) {
        traverse = traverse->next;
    }
    
    //Create a new node
    Node *p = new Node(traverse, traverse->next, value);

    //Update the previous node's *next
    traverse->next = p;
    
    //Update the following node's *prev
    p->next->prev = p;
        
    m_size++;
    
    return pos;
}

int Sequence::insert(const ItemType& value)
{

    Node *traverse = dummy; //traverse points to the Node right before
    
    int i;
    for (i = 0; i < m_size; i++) {
        traverse = traverse->next;
        if (value <= traverse->value) {
            break;
        }
    }

    //Create a new node
    Node *p = new Node(traverse, traverse->next, value);

    //Update the previous node's *next
    traverse->next = p;

    //Update the following node's *prev
    p->next->prev = p;

    m_size++;

    return i;
}

bool Sequence::erase(int pos)
{
    if (pos < 0  ||  pos >= size())
    return false;

    Node *traverse = dummy; //traverse points to the Node right before
    for (int i = 0; i < pos; i++) {
        traverse = traverse->next;
    }
    
    //traverse points to the node right before the one we want to delete
    Node *toDelete = traverse->next;
    
    traverse->next = toDelete->next;
    toDelete->next->prev = traverse;
    
    delete toDelete;
    
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value)
{
    int count = 0;

    Node *ptr = dummy;
    for (int i = 0; i < m_size; i++) {
        ptr = ptr->next;
        if (ptr->value == value) {
            erase(i); //erase() already decrements m_size
            count++;
        }
    }

    return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0  ||  pos >= size())
        return false;
    
    Node *traverse = dummy; //traverse points to the Node right before
    for (int i = 0; i < pos; i++) {
        traverse = traverse->next;
    }
    
    value = traverse->next->value;
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0  ||  pos >= size())
        return false;
    
    Node *traverse = dummy; //traverse points to the Node right before
    for (int i = 0; i < pos; i++) {
        traverse = traverse->next;
    }
    
    traverse->next->value = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
    Node *traverse = dummy;
    for (int i = 0; i < size(); i++) { //iterate through the linked list
        traverse = traverse->next;
        if (traverse->value == value) {
            return i;
        }
    }
    
    //No Node with that value was found
    return -1;
}

void Sequence::swap(Sequence& other)
{
    
    //Swap pointers to dummy nodes
    Node *ptrTemp = dummy;
    dummy = other.dummy;
    other.dummy = ptrTemp;
    

    // Swap sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

//int subsequence(const Sequence& seq1, const Sequence& seq2) {
//    if (seq2.empty()) return -1;
//
//}
