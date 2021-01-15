//
//  Sequence.cpp
//  homework1
//
//  Created by Grace Kwak on 1/13/21.
//

#include "Sequence.h"

#include <iostream>
#include <cassert>

Sequence::Sequence() {
    numItems = 0;
}

bool Sequence::empty() const {
    return numItems == 0;
}

int Sequence::size() const {
    return numItems;
}

int Sequence::insert(int pos, const ItemType& value) {
    
    if (pos > size()) return -1;
    
    for (int i = numItems; i > pos; i--) {
        sequence[i] = sequence[i-1];
    }
    sequence[pos] = value;
    numItems++;
    return pos;
}

int Sequence::insert(const ItemType& value) {
    
    if (size() > DEFAULT_MAX_ITEMS) return -1;
    
    for (int i = 0; i < size(); i++) {
        if (value <= sequence[i]) {
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
        sequence[i] = sequence[i+1];
    }
    
    numItems--;
    return true;
}

int Sequence::remove(const ItemType& value) {
    int numRemoved = 0;
    
    int i;
    for (i = 0; i < numItems; ) {
        if (sequence[i] == value) {
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
    value = sequence[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value) {
    if (pos < 0 || pos >= size()) return false;
    sequence[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const {
    for (int i = 0; i < size(); i++) {
        if (sequence[i] == value) {
            return i;
        }
    }
    
    return -1;
}

void Sequence::swap(Sequence& other) {
    
    int tempSize = size();
    numItems = other.size();
    other.numItems = tempSize;
    
    int max = size();
    if (other.size() > max) {
        max = other.size();
    }

    ItemType tempVal;
    for (int i = 0; i < max; i++) { //not so efficient but clean and simple
        tempVal = sequence[i];
        sequence[i] = other.sequence[i];
        other.sequence[i] = tempVal;
    }

//    for (int i = 0; i < numItems; i++) { //need temp var!!!
//        sequence[i] = other.sequence[i];
//    }
//
//    for (int i = 0; i < other.size(); i++) {
//        other.sequence[i] = sequence[i];
//    }
}

