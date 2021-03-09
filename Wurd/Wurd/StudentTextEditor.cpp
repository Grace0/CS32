#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <fstream>

TextEditor* createTextEditor(Undo* un)
{
	return new StudentTextEditor(un);
}

StudentTextEditor::StudentTextEditor(Undo* undo)
 : TextEditor(undo) {
     cursorPos.row = 0;
     cursorPos.col = 0;
     contents.push_back(""); //so that if we start typing on the first line, getLines will actually return something and our typed chars will show up on the screen
     curLine = contents.begin();
 }

StudentTextEditor::~StudentTextEditor()
{
	
}

bool StudentTextEditor::load(std::string file) {
    std::ifstream infile(file);
    if (!infile) {
        return false;
    }
    
    std::string line;
    while (getline(infile, line)) {
        if (line.back() == '\r') line.pop_back();
        contents.push_back(line);
    }
    
    cursorPos.row = contents.size()-1;
    curLine = contents.begin();
    curLine = std::next(curLine, cursorPos.row);
    cursorPos.col = contents.back().size();
    return true;
}

bool StudentTextEditor::save(std::string file) {
    std::ofstream outfile(file);
    if (!outfile) {
        return false;
    }
    
    for (std::list<std::string>::iterator it = contents.begin(); it != contents.end(); it++) {
        outfile << (*it) + '\n';
    }
    
	return true;
}

//TODO: Test
void StudentTextEditor::reset() {
    contents.clear();
    contents.push_back("");
    cursorPos.row = 0;
    curLine = contents.begin();
    cursorPos.col = 0;
}

void StudentTextEditor::move(Dir dir) {
    switch (dir) {
        case UP:
            if (cursorPos.row != 0) {
                cursorPos.row--;
                curLine--;
            }
            break;
        case DOWN:
            if (cursorPos.row != contents.size()-1) {
                cursorPos.row++;
                curLine++;
                
            }
            break;
        case LEFT:
            if (cursorPos.col == 0) {
                if (cursorPos.row != 0) {
                    cursorPos.row--;
                    curLine--;
                    cursorPos.col = curLine->size();
                }
            } else {
                cursorPos.col--;
            }
            break;
        case RIGHT:
            if (cursorPos.col == curLine->size()) {
                if (cursorPos.row != contents.size()-1) {
                    cursorPos.row++;
                    curLine++;
                    cursorPos.col = 0;
                }
            } else {
                cursorPos.col++;
            }
            break;
        case HOME:
            cursorPos.col = 0;
            break;
        case END:
            cursorPos.col = curLine->size();
            break;
    }
}

//TODO: Test
void StudentTextEditor::del() {
    
    if (cursorPos.col == (*curLine).size()) {
        if (curLine != contents.end()--) {
            *curLine = (*curLine) + (*(curLine++));
            contents.erase(curLine++);
        }
    } else {
        *curLine = (*curLine).erase(cursorPos.col, 1);
        cursorPos.col--;
    }
}

//TODO: Test
void StudentTextEditor::backspace() {
    
    if (cursorPos.col > 0) {
        *curLine = (*curLine).erase(cursorPos.col-1, 1);
        cursorPos.col--;
    } else if (cursorPos.col == 0 || (*curLine) == "" ) {
        if (curLine != contents.begin()) {
            curLine--;
            cursorPos.col = curLine->size();
            curLine->append(*(curLine++));
            contents.erase(curLine++);
            cursorPos.row--;
        }
    }
}

void StudentTextEditor::insert(char ch) {
    
    if (ch == '\t') {
        (*curLine).insert(cursorPos.col, "    ");
        cursorPos.col += 4;
    } else {
        std::string s(1, ch);
        (*curLine).insert(cursorPos.col, s);
        cursorPos.col++;
    }
}

//TODO: fix
void StudentTextEditor::enter() {
  
    contents.insert(curLine++, "");
    
    cursorPos.row++;
    curLine++;
    cursorPos.col = 0;
}

void StudentTextEditor::getPos(int& row, int& col) const {
	row = cursorPos.row; col = cursorPos.col;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
    
    if (startRow < 0 || numRows < 0 || startRow > contents.size()) return -1;
    
    if (startRow == contents.size()) {
        lines.clear();
        return lines.size();
    }
    
    lines.clear();
    std::list<std::string>::const_iterator it = contents.begin();
    
    auto curLine = std::next(it, startRow);
    
    for (int r = startRow; (r < (startRow + numRows)) && it != contents.end(); r++) {
        lines.push_back(*it);
        it++;
    }
    return lines.size();
}

void StudentTextEditor::undo() {
	// TODO
}
