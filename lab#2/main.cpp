#include <iostream>
#include <string>
#include <stdio.h>
#include <stack>
#include <math.h>
#include <fstream>

using namespace std;

// The basic algorithom of this calcultor program is to:
//   1) convert the input expression(infix expression) to postfix expression
//   2) evaluate the post expression 

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

// Declare all necessary function
bool isOperator(char);
bool isOperand(char);
bool hasPrecedence(char, char);
string convert(string);
double evaluatePostfix(string);

int main() {
    string infixExpression, postfixExpression;
    double ans;

    ifstream in_stream;
    //opening the file.
    in_stream.open("testCases.txt"); 

    if(!in_stream.fail()) {

        while (getline(in_stream, infixExpression)) {
            cout << "Expression: "<< infixExpression << endl;

            //Convert infix to postfix
            //The advantage of the postfix: allow to agnore parentheses when calculating
            postfixExpression = convert(infixExpression);
        
            //Compute the postfix
            ans = evaluatePostfix(postfixExpression);
            cout << "=> Result: " << ans << endl <<endl;
        }
    } 

    in_stream.close();
        
   return 0;
} // main-----------------------------------------------------------------------------------------


bool isOperand(char c) { 
    if (c >= '0' && c <= '9') {
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

// Function to return precedence of operators
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

// This function is used to convert the infix expression to the postfix expression
// Test Case: "1-16/4+2"
// Correct output: "1 16 4 / - 2 +"
// Since this is a digital calculator, the input only considered as digital numbers.
string convert(string infix) {
    stack<char> s;
    string postfix = "";
    //int digitCount = 0;

    for (int i = 0; i < infix.length(); i++) {
        char currentChar = infix[i];

        //Avoid extra empty sapce within the expression
        if (currentChar == ' ') {
            continue;

        } else if (currentChar == '(') {
            // If the case likes 1(1+2), auto push '*' into the string before pushing '('
            // If the case likes (1+1)(1+1), repeat the action.
            if ((infix[i-1] >= '0' && infix[i-1] <= '9') || infix[i-1] == ')') {
                s.push('*');
            }
            s.push(currentChar);

        } else if (isOperand(currentChar)) {
            // If points to a operand and if the previous character is ')', autofill a '*' into postfix at first.
            // Otherwise, treat it as a digit.
            if (infix[i-1] == ')') {
                s.push('*');
            }

            //In order to track multiple digits numbers, add an empty space if the next char is not a num
            postfix += currentChar;
            if (i != infix.length()-1 && !isOperand(infix[i+1])) {
                postfix += " ";
            } 
        
        } else if (isOperator(currentChar)) {
            // If the operator of the top of the stack has higher precedence than the current operator,
            // pop out the top of stack into postfix and then push the current operator into the stack.
            // Otherwise, push it directly.
            while (!s.empty() && prec(currentChar) <= prec(s.top())) {
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

    // Iterate the postfix expression
    for(int i = 0; i < postfix.length(); i++) {
        char currentChar = postfix[i];

        if (currentChar == ' ') {
            continue;

        }else if (isOperand(currentChar)) {
            int n = currentChar-48; // convert char to int
            digit = digit * 10 + (double)n; //initial digit = 0.0
            
            // When next char is ' ', it means the current digit is the last digit of this num.
            // Then, push the num to the stack and reset digits counter. 
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