#ifndef STUDENTTEXTEDITOR_H_
#define STUDENTTEXTEDITOR_H_

#include "TextEditor.h"
#include <string>

class Undo;

class LinkedList {
public:
    LinkedList() {
        head = new Node("", head, head);
        currentLine = head;
    }
    ~LinkedList() {}
    
    void addNode(std::string line) { //add to the end
        Node* newLine = new Node(line, head, currentLine);
        currentLine->prev = currentLine->next;
        currentLine->next = newLine;
        currentLine = newLine;
    }
    
private:
    struct Node {
        std::string line;
        Node* next;
        Node* prev;
        Node () {}
        Node (std::string l, Node* n, Node *p) {
            line = l;
            next = n;
            prev = p;
        }
    };
    
    Node* head;
    Node* currentLine;
};

class StudentTextEditor : public TextEditor {
public:

	StudentTextEditor(Undo* undo);
	~StudentTextEditor();
	bool load(std::string file);
	bool save(std::string file);
	void reset();
	void move(Dir dir);
	void del();
	void backspace();
	void insert(char ch);
	void enter();
	void getPos(int& row, int& col) const;
	int getLines(int startRow, int numRows, std::vector<std::string>& lines) const;
	void undo();

private:
    
    struct CursorPos {
        int row;
        int col;
    };
    
    CursorPos cursorPos;
    
    LinkedList contents;

};

#endif // STUDENTTEXTEDITOR_H_
