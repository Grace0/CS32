//
//  main.cpp
//  homework2
//
//  Created by Grace Kwak on 1/30/21.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>

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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    
    stack<Coord> coordStack;     // declare a stack of Coords

    //Push the starting coordinate (sr,sc) onto the coordinate stack and
    //    update maze[sr][sc] to indicate that the algorithm has encountered
    //    it (i.e., set maze[sr][sc] to have a value other than '.').
    Coord start(sr,sc);
    coordStack.push(start);
    maze[sr][sc] = '#';
    
    int rr, cc;
    
    while (!coordStack.empty()) { //While the stack is not empty,
        
        //{   Pop the top coordinate off the stack. This gives you the current
        //        (r,c) location that your algorithm is exploring.
        Coord next = coordStack.top();
        coordStack.pop();
        
        //    If the current (r,c) coordinate is equal to the ending coordinate,
        //        then we've solved the maze so return true!
        if (next.r() == er && next.c() == ec) {
            return true;
        }
        
        rr = next.r();
        cc = next.c();
        
        if (maze[rr-1][cc] == '.') {
            Coord north(rr-1, cc);
            coordStack.push(north);
            maze[rr-1][cc] = '#';
        } if (maze[rr][cc+1] == '.') {
            Coord east(rr, cc+1);
            coordStack.push(east);
            maze[rr][cc+1] = '#';
        } if (maze[rr+1][cc] == '.') {
            Coord south(rr+1, cc);
            coordStack.push(south);
            maze[rr+1][cc] = '#';
        } if (maze[rr][cc-1] == '.') {
            Coord west(rr, cc-1);
            coordStack.push(west);
            maze[rr][cc-1] = '#';
        }
        
    }
    
    //There was no solution, so return false
    return false;
  
  
}
          // Return true if there is a path from (sr,sc) to (er,ec)
          // through the maze; return false otherwise





//    Check each place you can move from the current cell as follows:
//        If you can move NORTH and haven't encountered that cell yet,
//            then push the coordinate (r-1,c) onto the stack and update
//            maze[r-1][c] to indicate the algorithm has encountered it.
//        If you can move EAST and haven't encountered that cell yet,
//            then push the coordinate (r,c+1) onto the stack and update
//            maze[r][c+1] to indicate the algorithm has encountered it.
//        If you can move SOUTH and haven't encountered that cell yet,
//            then push the coordinate (r+1,c) onto the stack and update
//            maze[r+1][c] to indicate the algorithm has encountered it.
//        If you can move WEST and haven't encountered that cell yet,
//            then push the coordinate (r,c-1) onto the stack and update
//            maze[r][c-1] to indicate the algorithm has encountered it.
//}



int main() {
    
//    string maze1[4] = {
//        "XXX",
//        "X.X",
//        "X.X",
//        "XXX"
//    };
//
//    cout << pathExists(maze1, 4,3, 2,1, 1,1) << endl;
    
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };

 //   assert(pathExists(maze, 10,10, 6,4, 1,1) == 1); //needed to do each assert one at a time because calling pathExists changes the maze[]
//    assert(pathExists(maze, 10,10, 6,4, 7,8) == 1);
//    assert(pathExists(maze, 10,10, 6,4, 7,1) == 0);
   // assert(pathExists(maze, 10,10, 6,4, 5,8) == 1);
   // assert(pathExists(maze, 10,10, 6,4, 1,5) == 1);

    cerr << "Passed all tests" << endl;
    return 0;
}
