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

//#include lines you need
//
//        declarations of any additional functions you might have written
//                to help you evaluate an expression
//
//        int evaluate(string infix, const bool values[], string& postfix, bool& result)
//        {
//            your expression evaluation code
//        }
//
//        implementations of any additional functions you might have written
//                to help you evaluate an expression
//
//        a main routine to test your function

void infixToPostfix(const string& infix, string& postfix) {
    postfix = "";
    stack<char> opStack;
    
    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        switch (ch) {
            case '(':
                opStack.push(ch);
                break;
            case ')':
                while (opStack.top() != '(') {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.pop();
                break;
            case '!': //ch is an operator
            case '&':
            case '|':
                while (!opStack.empty() && (opStack.top() != '(') && (ch >= opStack.top())) {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.push(ch);
                break;
            default: //ch is an operand
                postfix += ch;
                break;
        }
    }
    
    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }
}

int evaluate(string infix, const bool values[], string& postfix, bool& result) {
    
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
          // Evaluates a boolean expression
          //   If infix is a syntactically valid infix boolean expression,
          //   then set postfix to the postfix form of that expression, set
          //   result to the value of the expression (where in that expression,
          //   each digit k represents element k of the values array), and
          //   return zero.  If infix is not a syntactically valid expression,
          //   return 1.  (In that case, postfix may or may not be changed, but
          //   result must be unchanged.)

int main() {
    
    
//    0     1     2     3     4     5     6     7     8     9
//  true  true  true  false false false true  false true  false
//
//  2                          evaluates to true
//  (3)                        evaluates to false
//  2&(3)                      evaluates to false
//  0 & !9                     evaluates to true
//  !(7|8)                     evaluates to false
//  !7|8                       evaluates to true
//  6|4&5                      evaluates to true
//  1&!(9|1&1|9) | !!!(9&1&9)  evaluates to true
    
    bool ba[10] = {
                  //  0      1      2      3      4      5      6      7      8      9
                    true,  true,  true,  false, false, false, true,  false, true,  false
                };
    
    string infix = "ABC";
    string postfix = "0!!0!!&"; // T!=0    F!=1    F!F!|=1  F!T|=1  F!T&=1  F!F!&=1      T!T!|=0    T!T!&=0
    // 01&=TT&  03&=TF& 48&=FT& 99&=FF& , 01|=TT|   03|=TF|   48|=FT|  99|=FF|
    bool answer;
    evaluate(infix, ba, postfix, answer);
    cout << answer << endl; //false
    
//                string pf;
//                bool answer;
//                assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
//                assert(evaluate("8|", ba, pf, answer) == 1);
//                assert(evaluate(" &6", ba, pf, answer) == 1);
//                assert(evaluate("4 5", ba, pf, answer) == 1);
//                assert(evaluate("01", ba, pf, answer) == 1);
//                assert(evaluate("()", ba, pf, answer) == 1);
//                assert(evaluate("()4", ba, pf, answer) == 1);
//                assert(evaluate("2(9|8)", ba, pf, answer) == 1);
//                assert(evaluate("2(&8)", ba, pf, answer) == 1);
//                assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
//                assert(evaluate("x+5", ba, pf, answer) == 1);
//                assert(evaluate("", ba, pf, answer) == 1);
//                assert(evaluate("2|3|4", ba, pf, answer) == 0
//                                       &&  pf == "23|4|"  &&  answer);
//                assert(evaluate("2|(3|4)", ba, pf, answer) == 0
//                                       &&  pf == "234||"  &&  answer);
//                assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
//                                       &&  pf == "43!03&&|"  &&  !answer);
//                assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
//                ba[2] = false;
//                ba[9] = true;
//                assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
//                assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
//                cout << "Passed all tests" << endl;
}
