#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>
#include <set> //until Trie

class StudentSpellCheck : public SpellCheck {
public:
    StudentSpellCheck() { }
	virtual ~StudentSpellCheck();
	bool load(std::string dict_file);
	bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
	void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:

    std::set<std::string> dict;
    
};

class Trie {
public:
    
    struct Node {
        char letter;
        std::vector<Node*> branches;
        
        Node() {}
        Node(char l) { letter = l; }
    };
    
    Trie() {
        root = new Node;
    }
    ~Trie();
    
    bool addNode(char letter);
    
private:
    
    Node* root;
};

#endif  // STUDENTSPELLCHECK_H_
