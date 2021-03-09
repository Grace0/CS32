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
    cursorPos.col = contents.back().size()-1;
    return true;
}

bool StudentTextEditor::save(std::string file) {
	return false;  // TODO
}

void StudentTextEditor::reset() {
 //   contents.clear();
    cursorPos.row = 0;
    cursorPos.col = 0;
}

void StudentTextEditor::move(Dir dir) {
	// TODO
}

void StudentTextEditor::del() {
	// TODO
}

void StudentTextEditor::backspace() {
	// TODO
}

void StudentTextEditor::insert(char ch) {
    //get reference to current line
    cursorPos.col++;
}

void StudentTextEditor::enter() {
	// TODO
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
    std::list<std::string>::iterator it;
    for (int i = 0; i < startRow; i++) {
        it++;
    }
    
    for (int r = startRow; (r < (startRow + numRows)) && it != contents.end(); r++) {
        lines.push_back(*it);
        it++;
    }
    return lines.size();
}

void StudentTextEditor::undo() {
	// TODO
}
