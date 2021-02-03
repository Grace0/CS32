//
//  eval.cpp
//  homework2
//
//  Created by Grace Kwak on 1/30/21.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>

using namespace std;

bool hasHigherPrecedence(char a, char b) {

    const char arr[3] = { '!' , '&', '|' };
    
    for (int i = 0; i < 3; i++) {
        if (arr[i] == a) {
            return true;
        } else if (arr[i] == b) {
            return false;
        }
    }
    return true;
}

bool infixToPostfix(string& infix_p, string& postfix) {
    postfix = "";
    stack<char> opStack;
  
    string infix = ""; //remove spaces from infix
    for (int i = 0; i < infix_p.length(); i++) {
        if (infix_p[i] != ' ') {
            infix += infix_p[i];
        }
    }
   
    int count = 0; //there should be an even # of parenthesis
    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '(' || infix[i] == ')') {
            count++;
        }
    }
    if (count % 2 != 0) return false;
    
    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        switch (ch) {
            case '(':
                if (i == infix.length()-1) return false;
                if (infix[i+1] == '&' || infix[i+1] == '|') return false;
                opStack.push(ch);
                break;
            case ')':
                if (i == 0) return false;
                while (opStack.top() != '(') {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.pop();
                break;
            case '!': //ch is a UNARY operator
                if (i == infix.length()-1) return false;
                if (infix[i+1] == '&' || infix[i+1] == '|' || infix[i+1] == ')') return false;
                if (i != 0 && (isdigit(infix[i-1]) || infix[i-1] == '(' || infix[i-1] == ')')) return false;
                opStack.push(ch);
                break;
            case '&':
            case '|':
                if (i == 0 || i == infix.length()-1) return false;
                if (infix[i-1] == '|' || infix[i-1] == '&' || infix[i-1] == '!' || infix[i-1] == '(' || infix[i-1] == ')') {
                    return false;
                }
                while (!opStack.empty() && (opStack.top() != '(') && hasHigherPrecedence(opStack.top(), ch)) {  //ch has smaller prcedence
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.push(ch);
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': //ch is an operand
                
                if (i != 0) { //if we're not at index 0 and the previous index is also a digit
                    if (isdigit(infix[i-1]) || infix[i-1] == ')') {
                        return false;
                    }
                }
                 
                if (i != infix.length()-1) {
                    if (infix[i+1] == '!' || infix[i+1] == '(') {
                            return false;
                    }
                }
                postfix += ch;
                break;
            default: //ch is some not-allowed char
                return false;
                break;
        }
    }
    
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }
    
    if (postfix == "") return false;
    
    return true;
}

int evaluate(string infix, const bool values[], string& postfix, bool& result) {
    
    if (!infixToPostfix(infix, postfix)) return 1;
    
    stack<bool> evalStack;
    bool op1, op2, res; //res of the individual op
    
    char currChar;
    
    for (int i = 0; i < postfix.length(); i++) {
        
        currChar = postfix[i];
        
        if (currChar == '!') {
            
            op1 = evalStack.top();
            evalStack.pop();
            
            res = !op1;
            evalStack.push(res);
            
        } else if (currChar == '&') {
            
            op2 = evalStack.top();
            evalStack.pop();
            
            op1 = evalStack.top();
            evalStack.pop();
            
            res = op1 && op2;
            evalStack.push(res);
            
        } else if (currChar == '|') {
            
            op2 = evalStack.top();
            evalStack.pop();
            
            op1 = evalStack.top();
            evalStack.pop();
            
            res = op1 || op2;
            evalStack.push(res);
            
        } else { //currChar is a digit
            evalStack.push(values[currChar-'0']);
        }
        
    }
    result = evalStack.top();
    return 0;
}
