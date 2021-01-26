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
    
    delete deleteFirst; //delete the last node
}

Sequence::Sequence(const Sequence& src) {
    
    m_size = 0; //initialize m_size to 0
    
    dummy = new Node;
    dummy->next = dummy;
    dummy->prev = dummy;
    
    Node *ptr = src.dummy;
    
    for (int i = 0; i < src.m_size; i++) { //call insert() for however many nodes are in src
        ptr = ptr->next;
        insert(i, ptr->value); //insert() will increment m_size
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

    Node *ptr = dummy->next;
        
    for (int i = 0; i < m_size; ) {
        if (ptr->value == value) {
            ptr = ptr->next; // after we call erase(), the ptr to Node i will be a dangling pointer, so before we delete that node, we increment ptr to point to the Node i+1, which will be the new Node i (after we call erase()) //we only increment ptr when we do find a value to remove
            erase(i); //erase() already decrements m_size
            count++;
        } else {
            i++;
            ptr = ptr->next;
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

int subsequence(const Sequence& seq1, const Sequence& seq2) {
    if (seq1.empty() || seq2.empty() || (seq1.size() < seq2.size())) return -1;
    
    ItemType seq1Val;
    ItemType seq2Val;
    
    ItemType seq2FirstVal;
    seq2.get(0, seq2FirstVal);
    
    int next;
    for (int pos = 0; pos < seq1.size()-seq2.size()+1; pos++) {
        seq1.get(pos, seq1Val);
        if (seq1Val == seq2FirstVal) {
            for (next = 1; next < seq2.size(); next++) {
                seq1.get(pos + next, seq1Val);
                seq2.get(next, seq2Val);
                if (seq1Val != seq2Val) {
                    break; //break out of the for() loop because we know it's not a match
                }
            }
            if (next == seq2.size()) { //we made it though the entire for()
                return pos;
            }
        }
    }

    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    
    //Empty the result
    while (!result.empty()) {
        result.erase(0);
    }
    
    if (seq1.empty() && seq2.empty()) {
        return;
    }
    
    
    if (seq1.empty()) {
        result = seq2; //AO
        return;
    }
    
    if (seq2.empty()) {
        result = seq1;
        return;
    }

    
    //if m = n
    ItemType one, two;
    for (int i = 0; i < seq1.size(); i++) {
        seq1.get(i, one);
        seq2.get(i, two);
        
        result.insert(result.size(), one); //add to the end of the sequence
        result.insert(result.size(), two);
    }

}
