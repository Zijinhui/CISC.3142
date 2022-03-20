#include <iostream>
#include<bits/stdc++.h>
#include <string>
#include <stdio.h>
#include <stack>

using namespace std;

struct Calculator {
    enum operators {
        add = '+',
        minus = '-',
        multiply = '*',
        divide = '/'
    };

    double compute(string num1, string num2, char op) {
        //struct Calculator cal;
        double result = 0.0;
        cout << "Compute: "<< num1 << num2 << endl;
        double a = std::stod(num1);
        double b = std::stod(num2);
        
        switch(op) {
            case Calculator::add:
                result = a + b;
                break;
            case Calculator::minus:
                result = a - b;
                break;
            case Calculator::multiply:
                result = a * b;
                break;
            case Calculator::divide:
                result = a / b;
        }
        return result;
    }
    
};


bool isOperator(char);
bool isOperand(char);
bool hasPrecedence(char, char);
string convert(string);
double evaluatePostfix(string);

int main() {
    string infixExpression, postfixExpression;
    double ans;
    cout << "Please enter the expression: ";
    
    //use getline() to get entire expression
    getline(cin, infixExpression);
    cout << infixExpression << endl;
    //printf("\n%s",infixExpression);
    
    //convert infix to postfix
   postfixExpression = convert(infixExpression);
    cout << postfixExpression << endl;
    
    //Compute postfix
    ans = evaluatePostfix(postfixExpression);
    cout << "Final total: " << ans;

    // struct Calculator cal;
    // char sign = Calculator :: add;
    // double a = cal.compute("3","4",sign);
    // printf("Test: %.2f", a);
    // a = cal.compute("4", "5",Calculator :: multiply);
    // printf("Test: %.2f", a);
    //printf("Test: %.2f", b);
   
   
   return 0;
}

// struct Calculator cal;
// char sign = Calculator :: add;
// double a = cal.compute("3","4",sign);
// printf("Test: %.2f", a);
// return 0;


bool isOperand(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
        return true;
    }
    return false;
}
bool isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ) {
        return true;
    }
    return false;
}

//Function to return precedence of operators
int prec(char c) {
    if(c == '^')
        return 3;
    else if(c == '/' || c=='*')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// this function is used to convert the infix expression to the postfix expression
// Test Case: (A*(B+D)/E)-F*(G+H/K)
// Correct output: ABD+E/*FGHK/+*-
string convert(string infix) {
    stack<char> s;
    string postfix = "";
    int digitCount = 0;

    for (int i = 0; i < infix.length(); i++) {
        char currentChar = infix[i];

        //avoid extra empty sapce within the expression
        if (currentChar == ' ') {
            continue;

        } else if (currentChar == '(') {
            s.push(currentChar);

        } else if (isOperand(currentChar)) {
            digitCount++;
            postfix += currentChar;
            if (i != infix.length()-1 && !isOperand(infix[i+1])) {
                postfix += " ";
                digitCount = 0;
            } 
        
        } else if (isOperator(currentChar)) {
            // If the operator of the top of the stack has higher precedence than the current operator,
            // pop out the top of stack into postfix and then push the current operator into the stack.
            // Otherwise, push it directly.
            while (!s.empty() && prec(currentChar) < prec(s.top())) {
                postfix += s.top(); // peek the top index
                postfix += " ";
                s.pop(); // pop out
            }
            s.push(currentChar);
        }else if (currentChar == ')') {
            while(s.top() != '(') {
                postfix += s.top();
                postfix += " ";
                s.pop();
            }
            s.pop(); // pop ')' out
        }
    }
    // Pop all the remaining elements from the stack
    while(!s.empty()) {
        postfix += " ";
        postfix += s.top();    
        s.pop();
    }

    return postfix;
}

double evaluatePostfix(string postfix) {
    stack<double> result;
    //double value;
    struct Calculator cal;

    cout << "evaluatePostfix TEST" << endl;
    for(int i = 0; i < postfix.length(); i++) {
        string num22;
        string num11;
       
        cout << postfix[i] << endl;
        char currentChar = postfix[i];

        if (currentChar == ' ') {
            continue;
        }else if (isOperand(currentChar)) {
            result.push(currentChar);
        } else if (isOperator(currentChar)) {
            char num2 = result.top();
            
            result.pop(); // pop num2
            char num1 = result.top();
            
            result.pop(); // pop num1

            string num22(1, num2);
            string num11(1, num1);
            // num22+=num2;
            // num11+=num1;

            double value = cal.compute(num11, num22, currentChar);
            cout << "Value: "<< value << endl;
            result.push(value); // push the value
            
        }
    }
    return result.top();

}