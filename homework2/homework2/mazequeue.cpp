//
//  main.cpp
//  homework2
//
//  Created by Grace Kwak on 1/30/21.
//

#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Coord
{
  public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};

//implementation is exactly the same as for stacks; just replace all vars with "queue"
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    
    queue<Coord> coordQueue;       // declare a queue of Coords

    //Push the starting coordinate (sr,sc) onto the coordinate stack and
    //    update maze[sr][sc] to indicate that the algorithm has encountered
    //    it (i.e., set maze[sr][sc] to have a value other than '.').
    Coord start(sr,sc);
    coordQueue.push(start);
    maze[sr][sc] = '#';
    
    int rr, cc;
    
    while (!coordQueue.empty()) { //While the stack is not empty,
        
        //{   Pop the top coordinate off the stack. This gives you the current
        //        (r,c) location that your algorithm is exploring.
        Coord next = coordQueue.front();
        coordQueue.pop();
        
        //    If the current (r,c) coordinate is equal to the ending coordinate,
        //        then we've solved the maze so return true!
        if (next.r() == er && next.c() == ec) {
            return true;
        }
        
        rr = next.r();
        cc = next.c();
        
        if (maze[rr-1][cc] == '.') {
            Coord north(rr-1, cc);
            coordQueue.push(north);
            maze[rr-1][cc] = '#';
        } if (maze[rr][cc+1] == '.') {
            Coord east(rr, cc+1);
            coordQueue.push(east);
            maze[rr][cc+1] = '#';
        } if (maze[rr+1][cc] == '.') {
            Coord south(rr+1, cc);
            coordQueue.push(south);
            maze[rr+1][cc] = '#';
        } if (maze[rr][cc-1] == '.') {
            Coord west(rr, cc-1);
            coordQueue.push(west);
            maze[rr][cc-1] = '#';
        }
        
    }
    
    //There was no solution, so return false
    return false;
  
}
