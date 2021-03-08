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
	// TODO
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
    
    cursorPos.row = contents.size();
    cursorPos.col = contents.back().size();
    return true;  // TODO
}

bool StudentTextEditor::save(std::string file) {
	return false;  // TODO
}

void StudentTextEditor::reset() {
	// TODO
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
	// TODO
}

void StudentTextEditor::enter() {
	// TODO
}

void StudentTextEditor::getPos(int& row, int& col) const {
	row = 0; col = 0; // TODO
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
	return 0; // TODO
}

void StudentTextEditor::undo() {
	// TODO
}
