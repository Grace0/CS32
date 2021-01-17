//
//  Sequence.cpp
//  homework1
//
//  Created by Grace Kwak on 1/13/21.
//

#include "newSequence.h"

#include <iostream>
#include <cassert>

Sequence::Sequence() {
    m_maxItems = DEFAULT_MAX_ITEMS;
    m_sequence = new ItemType[m_maxItems];
    m_numItems = 0;
}

Sequence::Sequence(const int MAX_ITEMS) {
    m_maxItems = MAX_ITEMS;
    m_sequence = new ItemType[m_maxItems];
    m_numItems = 0;
}

Sequence::Sequence(const Sequence& src) {
    
    m_maxItems = src.m_maxItems;
    m_numItems = src.m_numItems;
    m_sequence = new ItemType[m_maxItems];
    
    for (int i = 0; i < m_numItems; i++) {
        m_sequence[i] = src.m_sequence[i];
    }
    
   //don't need to return anything; it's just another constructor
}

Sequence& Sequence::operator=(const Sequence &src) { //return_type class_name function_name

    if (&src == this) return *this; //why do we do &src instead of &this?

    delete [] m_sequence;

    m_maxItems = src.m_maxItems;
    m_numItems = src.m_numItems;

    m_sequence = new ItemType[m_maxItems];

    for (int i = 0; i < m_numItems; i++) {
        m_sequence[i] = src.m_sequence[i];
    }
    
    return *this;
}

Sequence::~Sequence() {
    delete[] m_sequence;
}

bool Sequence::empty() const {
    return m_numItems == 0;
}

int Sequence::size() const {
    return m_numItems;
}

int Sequence::insert(int pos, const ItemType& value) {
    
    if (pos > size()) return -1;
    
    for (int i = m_numItems; i > pos; i--) {
        m_sequence[i] = m_sequence[i-1];
    }
    m_sequence[pos] = value;
    m_numItems++;
    return pos;
}

int Sequence::insert(const ItemType& value) {
    
    if ((m_numItems + 1) > m_maxItems) return -1; //if by adding one, we would go over the max size
    
    for (int i = 0; i < size(); i++) {
        if (value <= m_sequence[i]) {
            insert(i, value);
            return i;
        }
    }
    
    int p = size();
    insert(size(), value);
    return p;
}

bool Sequence::erase(int pos) {
    if (pos < 0 || pos >= size()) return false;
    
    for (int i = pos; i < size() - 1; i++) {
        m_sequence[i] = m_sequence[i+1];
    }
    
    m_numItems--;
    return true;
}

int Sequence::remove(const ItemType& value) {
    int numRemoved = 0;
    
    int i;
    for (i = 0; i < m_numItems; ) {
        if (m_sequence[i] == value) {
            erase(i);
            numRemoved++;
        } else {
            i++; //only increment if we didn't remove something at that pos
        }
    }
    return numRemoved;
}

bool Sequence::get(int pos, ItemType& value) const {
    if (pos < 0 || pos >= size()) return false;
    value = m_sequence[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value) {
    if (pos < 0 || pos >= size()) return false;
    m_sequence[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const {
    for (int i = 0; i < size(); i++) {
        if (m_sequence[i] == value) {
            return i;
        }
    }
    
    return -1;
}

void Sequence::swap(Sequence& other) {
    
    unsigned long *temp = other.m_sequence;
    other.m_sequence = m_sequence;
    m_sequence = temp;
    
    int tempSize = m_numItems;
    m_numItems = other.size();
    other.m_numItems = tempSize;
    
    int tempMax = m_maxItems;
    m_maxItems = other.m_maxItems;
    other.m_maxItems = tempMax;
    
    
//    int tempSize = size();
//    m_numItems = other.size();
//    other.m_numItems = tempSize;
//
//    int max = size();
//    if (other.size() > max) {
//        max = other.size();
//    }
//
//    ItemType tempVal;
//    for (int i = 0; i < max; i++) { //not so efficient but clean and simple
//        tempVal = m_sequence[i];
//        m_sequence[i] = other.m_sequence[i];
//        other.m_sequence[i] = tempVal;
//    }

//    for (int i = 0; i < m_numItems; i++) { //need temp var!!!
//        m_sequence[i] = other.m_sequence[i];
//    }
//
//    for (int i = 0; i < other.size(); i++) {
//        other.m_sequence[i] = m_sequence[i];
//    }
}

