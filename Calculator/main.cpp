#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <math.h>

using namespace std;

struct Calculator {
    enum operators {
        add = '+',
        minus = '-',
        multiply = '*',
        divide = '/',
        exponent = '^'
    };

    double compute(double num1, double num2, char op) {
        double result = 0.0;
        
        switch(op) {
            
            case Calculator::add:
                result = num1 + num2;
                break;
            
            case Calculator::minus:
                result = num1 - num2;
                break;
            
            case Calculator::multiply:
                result = num1 * num2;
                break;
            
            case Calculator::divide:
                result = num1 / num2;
                break;
            
            case Calculator::exponent:      
                result = pow(num1, num2);
                break; 
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
    char retry;

    do {     
        cout << "Please enter the expression: ";
    
        //use getline() to get entire expression
        getline(cin, infixExpression);

        //convert infix to postfix
        postfixExpression = convert(infixExpression);
    
        //Compute postfix
        ans = evaluatePostfix(postfixExpression);
        cout << "Result: " << ans << endl;
        cout << "Stay for a new calculation? y for yes && n for no" << endl;
        cin >> retry;
    }while(retry == 'y');
   
   return 0;
}

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

// function to return precedence of operators
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
    struct Calculator cal;
    double digit = 0.0;

    for(int i = 0; i < postfix.length(); i++) {
        char currentChar = postfix[i];

        if (currentChar == ' ') {
            continue;

        }else if (isOperand(currentChar)) {
            int n = currentChar-48; // convert char to int
            digit = digit * 10 + (double)n; //initial digit = 0.0
            
            if (postfix[i+1] == ' ') {
                result.push(digit);
                digit = 0.0; //reset total
            }

        } else if (isOperator(currentChar)) {
            double num2 = result.top();           
            result.pop(); // pop num2
            double num1 = result.top();         
            result.pop(); // pop num1

            double value = cal.compute(num1, num2, currentChar);
            result.push(value); // push the value       
        }
    }
    return result.top();

}