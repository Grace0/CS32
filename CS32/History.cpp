//
//  History.cpp
//  CS32
//
//  Created by Grace Kwak on 1/9/21.
//

#include "History.h"

//using namespace std;

History::History(int nRows, int nCols)
{
    m_nRows = nRows;
    m_nCols = nCols;
    
    for (int r = 0; r < m_nRows; r++) {
        for (int c = 0; c < m_nCols; c++) {
            historyGrid[r][c] = '.';
        }
    }
}

bool History::record(int r, int c) {
    return false;
}

void History::display() const {
   clearScreen();
    
    for (int r = 0; r < m_nRows; r++)
    {
        for (int c = 0; c < m_nCols; c++)
            std::cout << historyGrid[r][c];
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
}
