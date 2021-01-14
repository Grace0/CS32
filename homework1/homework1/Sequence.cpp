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

bool Sequence::get(int pos, ItemType& value) {
    
}
//  // If 0 <= pos < size(), copy into value the item at position pos
//  // of the sequence and return true.  Otherwise, leave value unchanged
//  // and return false.
//
//bool set(int pos, const ItemType& value);
//  // If 0 <= pos < size(), replace the item at position pos in the
//  // sequence with value and return true.  Otherwise, leave the sequence
//  // unchanged and return false.

//int find(const ItemType& value) const;
  // Let p be the smallest integer such that value == the item at
  // position p in the sequence; if no such item exists, let p be -1.
  // Return p.

//void swap(Sequence& other);
  // Exchange the contents of this sequence with the other one.
