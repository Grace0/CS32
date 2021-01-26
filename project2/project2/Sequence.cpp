// Sequence.cpp

#include "Sequence.h"

Sequence::Sequence()
 : m_size(0)
{
    //Initialize a dummy node, circularly and doubly linked
    dummy = new Node;
    dummy->next = dummy;
    dummy->prev = dummy;

}

Sequence::~Sequence() {
    
    Node *deleteFirst = dummy;
    
    //Loop through all list nodes and call delete
    for (int i = 0; i < m_size; i++) {
        Node *deleteNext = deleteFirst->next;
        delete deleteFirst;
        deleteFirst = deleteNext;
    }
    
    delete deleteFirst; //delete the last node
}

Sequence::Sequence(const Sequence& src) {
    
    m_size = 0; //initialize m_size to 0
    
    //Create a new dummy node for the new list
    dummy = new Node;
    dummy->next = dummy;
    dummy->prev = dummy;
    
    Node *ptr = src.dummy;
    
    //"Copy" each node over to the new list by calling insert()
    for (int i = 0; i < src.m_size; i++) { //call insert() for however many nodes are in src
        ptr = ptr->next;
        insert(i, ptr->value); //insert() will increment m_size
    }

}

Sequence& Sequence::operator=(const Sequence& src) {
    
    //Copy src to a temporary Sequence, since src itself is const
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
    
    //Move to the node position where we want to insert the new node
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
    
    //Re-adjust links
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
        
    //Loop through each node
    for (int i = 0; i < m_size; ) {
        if (ptr->value == value) {
            ptr = ptr->next; // after we call erase(), the ptr to Node i will be a dangling pointer, so before we delete that node, we increment ptr to point to the Node i+1, which will be the new Node i (after we call erase())
            erase(i); //erase() already decrements m_size
            count++;
        } else {
            i++; //We only increment i when we haven't found (and deleted) a node at i
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
    for (int pos = 0; pos < seq1.size()-seq2.size()+1; pos++) { //iterate though the nodes in seq1 that could be the start of a subsequence seq2
        seq1.get(pos, seq1Val);
        
        if (seq1Val == seq2FirstVal) {
            
            for (next = 1; next < seq2.size(); next++) { //iterate though the next consecutive nodes in seq1 to check if they correspond to each of the remaining nodes in seq2
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
    
    if (seq1.empty() && seq2.empty()) {
        while (!result.empty()) {
            result.erase(0);
        }
        return;
    }
    
    if (seq1.empty()) {
        result = seq2;
        return;
    }
    
    if (seq2.empty()) {
        result = seq1;
        return;
    }
    
    //Create a temp Sequence that we will use to create the result Sequence without changing seq1 and seq2
    Sequence thisResult;

    bool seq1IsBigger; //to determine which seq may have items left over, to add to the end of Result
    int smallerSize; //to determine the positions of the extra nodes in the longer seq
    int largerSize;
    
    if (seq1.size() > seq2.size()) {
        smallerSize = seq2.size();
        largerSize = seq1.size();
        seq1IsBigger = true;
    } else {
        smallerSize = seq1.size();
        largerSize = seq2.size();
        seq1IsBigger = false;
    }
    
    ItemType one, two;
    //Up until we run out of nodes in the smaller seq, we alternate inserting the nodes into Result
    for (int i = 0; i < smallerSize; i++) {
        seq1.get(i, one);
        seq2.get(i, two);
        
        thisResult.insert(thisResult.size(), one); //add to the end of the sequence
        thisResult.insert(thisResult.size(), two);
    }
    
    //Once we run out of nodes in the smaller seq, we insert the remaining nodes of the longer sequence into Result
    if (seq1IsBigger) {
        for (int j = smallerSize; j < largerSize; j++) {
            seq1.get(j, one);
            thisResult.insert(thisResult.size(), one);
        }
    } else {
        for (int j = smallerSize; j < largerSize; j++) {
            seq2.get(j, two);
            thisResult.insert(thisResult.size(), two);
        }
    }

    result = thisResult;

}
