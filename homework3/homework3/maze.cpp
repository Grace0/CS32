//
//  maze.cpp
//  homework3
//
//  Created by Grace Kwak on 2/7/21.
//

#include <iostream>
#include <cassert>
#include <string>

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
    if (sr == er && sc == ec) {
        return true;
    }
    
    maze[sr][sc] = '#';
    
    if (maze[sr-1][sc] == '.') { //north
        if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec)) return true;
    }
    if (maze[sr][sc+1] == '.') { //east
        if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec)) return true;
    }
    if (maze[sr+1][sc] == '.') { //south
        if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec)) return true;
    }
    if (maze[sr][sc-1] == '.') { //west
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec)) return true;
    }
    
    return false;
    
}

//int main() {
//    
////        string maze1[4] = {
////            "XXX",
////            "X.X",
////            "X.X",
////            "XXX"
////        };
////
////        cout << pathExists(maze1, 4,3, 2,1, 1,1) << endl;
//    
//        string maze[10] = {
//            "XXXXXXXXXX",
//            "X........X",
//            "XX.X.XXXXX",
//            "X..X.X...X",
//            "X..X...X.X",
//            "XXXX.XXX.X",
//            "X.X....XXX",
//            "X..XX.XX.X",
//            "X...X....X",
//            "XXXXXXXXXX"
//        };
//    
//   //     assert(pathExists(maze, 10,10, 6,4, 1,1) == 1); //needed to do each assert one at a time because calling pathExists changes the maze[]
//    //    assert(pathExists(maze, 10,10, 6,4, 7,8) == 1);
//    //    assert(pathExists(maze, 10,10, 6,4, 7,1) == 0);
//     //   assert(pathExists(maze, 10,10, 6,4, 5,8) == 1);
//        assert(pathExists(maze, 10,10, 6,4, 1,5) == 1);
//    cout << "Passed all tests" << endl;
//}
