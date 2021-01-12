//
//  History.hpp
//  CS32
//
//  Created by Grace Kwak on 1/9/21.
//

#ifndef History_h
#define History_h

#include <iostream>
#include "globals.h" //why couldn't I do #include utilities.cpp ?

class History
{
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;

private:
    
    int m_nRows, m_nCols;
    char historyGrid[MAXROWS][MAXCOLS];
    
};

#endif /* History_hpp */
