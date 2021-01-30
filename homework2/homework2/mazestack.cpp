//
//  main.cpp
//  homework2
//
//  Created by Grace Kwak on 1/30/21.
//

#include <iostream>
#include <string>
#include <stack>

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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
          // Return true if there is a path from (sr,sc) to (er,ec)
          // through the maze; return false otherwise

//Push the starting coordinate (sr,sc) onto the coordinate stack and
//    update maze[sr][sc] to indicate that the algorithm has encountered
//    it (i.e., set maze[sr][sc] to have a value other than '.').
//While the stack is not empty,
//{   Pop the top coordinate off the stack. This gives you the current
//        (r,c) location that your algorithm is exploring.
//    If the current (r,c) coordinate is equal to the ending coordinate,
//        then we've solved the maze so return true!
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
//There was no solution, so return false


int main() {
    
    stack<Coord> coordStack;     // declare a stack of Coords

    Coord a(5,6);
    coordStack.push(a);          // push the coordinate (5,6)
    coordStack.push(Coord(3,4)); // push the coordinate (3,4)
   
    Coord b = coordStack.top();  // look at top item in the stack
    coordStack.pop();            // remove the top item from stack
    if (coordStack.empty())      // Is the stack empty?
        cout << "empty!" << endl;
    cout << coordStack.size() << endl;  // number of elements
    
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X........X",
//        "XX.X.XXXXX",
//        "X..X.X...X",
//        "X..X...X.X",
//        "XXXX.XXX.X",
//        "X.X....XXX",
//        "X..XX.XX.X",
//        "X...X....X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10,10, 6,4, 1,1))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;

    return 0;
}
