//
//  History.hpp
//  CS32
//
//  Created by Grace Kwak on 1/9/21.
//

#ifndef History_h
#define History_h

class History
{
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;

private:
   
};

#endif /* History_hpp */
