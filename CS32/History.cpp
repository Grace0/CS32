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
            historyGrid[r][c] = 'A' - 1;
        }
    }
}

bool History::record(int r, int c) {
    
    if (r >= m_nRows || c >= m_nCols || r < 1 || c < 1) {
        return false;
    }
    
    historyGrid[r][c]++;
    return true;
}

void History::display() const {
   clearScreen();
    
    for (int r = 0; r < m_nRows; r++)
    {
        for (int c = 0; c < m_nCols; c++) {
            if (historyGrid[r][c] == 'A' - 1) {
                std::cout << '.';
            } else if (historyGrid[r][c] >= 'A' + 25) {
                std::cout << 'Z';
            } else {
                std::cout << historyGrid[r][c];
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
}
