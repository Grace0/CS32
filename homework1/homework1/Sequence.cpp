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

//bool erase(int pos);
//  // If 0 <= pos < size(), remove the item at position pos from
//  // the sequence (so that all items that followed that item end up at
//  // positions one lower than they were at before), and return true.
//  // Otherwise, leave the sequence unchanged and return false.
//
//int remove(const ItemType& value);
//  // Erase all items from the sequence that == value.  Return the
//  // number of items removed (which will be 0 if no item == value).
//
//bool get(int pos, ItemType& value);
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
