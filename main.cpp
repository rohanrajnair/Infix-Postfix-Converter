//  main.cpp
//  HW01
//
//  Created by Rohan Nair on 4/8/17.
//  Copyright © 2017 Rohan Nair. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

bool isOperator(char c);

string reverse(string s);

void infixToPrefix(string s);

void prefixToInfix(stack<char> &my_stack);

int main(){
    string b;
    //enter infix like: (3+2)
    //enter postfix like: + 3 2
    cout << "enter an expression in infix with parentheses or in prefix with spaces: " << endl;
    getline(cin,b);
    if (isOperator(b[0])){
        b = reverse(b);
        stack<char> s;
        for (int i = 0; i < b.length(); ++i){
            s.push(b[i]);
        }
        cout << "infix notation: ";
        prefixToInfix(s);
    }
    else{
        cout << "prefix notation: ";
        infixToPrefix(b);
    }
}

void infixToPrefix(string s){
    stack<string> operators;
    stack<string> final_expression;
    s = reverse(s);
    string temp = "";
    for (int i = 0; i < s.length(); ++i){
        if (isdigit(s[i])){
            temp = s[i] +  temp;
        }
        
        else{

            if (temp.length() > 0){
                final_expression.push(temp);
                temp = "";
            }
            
            if (isOperator(s[i])){
                stringstream ss;
                ss << s[i];
                operators.push(ss.str());
            }
            if (s[i] == ')'){
                stringstream ss;
                ss << s[i];
                operators.push(ss.str());
            }
            if (s[i] == '('){
                bool b = 1;
                while (b){
                    final_expression.push(operators.top());
                    operators.pop();
                    if (operators.top() == ")"){
                        operators.pop();
                        b = 0;
                    }
                }
            }
        }
    }
    
    while (!final_expression.empty()){
        string top = final_expression.top();
                if (top.length() > 1){
                    stoi(top);
                    cout << top << " ";
                }
                else{
                    if(isdigit(top[0])){
                        stoi(top);
                        cout << top << " ";
                    }
                    else{
                        cout << final_expression.top() << " ";
                    }
                }
        final_expression.pop();
        }
        cout << endl;
}
bool isOperator(char c){
    if ((c == '+') || (c == '-') || (c == '*') || (c == '/')){
        return true;
    }
    else{
        return false;
    }
}

string reverse(string s){
    string s2 = s;
    int j = 0;
    for (int i = s.length()-1; i >=0; --i){
        s2[j] = s[i];
        ++j;
    }
    return s2;
}


void prefixToInfix(stack<char> &my_stack){
    
    if (my_stack.empty())
        return;
    
    char tmp = my_stack.top();
    my_stack.pop();
    if (isOperator(tmp)) {
        cout << "(";
        prefixToInfix(my_stack);
        cout << tmp;
        prefixToInfix(my_stack);
        cout << ")";
    } else if (tmp == ' ') {
        prefixToInfix(my_stack);
    } else {
        cout << tmp;
        
        if (my_stack.empty())
            return;
        
        if (my_stack.top() != ' ') {
            prefixToInfix(my_stack);
        }
    }
}
