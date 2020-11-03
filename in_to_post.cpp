#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <string.h>
#include <cmath>
#include <fstream>
using namespace std;

int priority(char a)
{
    if (a == '^') return 1;
    if (a == '*' || a == '/') return 2;
    if (a == '+' || a == '-') return 3;
    return 4;    
}

float eval(char operation, float operand1, float operand2)
{
    if (operation == '+') return operand1 + operand2;
    if (operation == '-') return operand1 - operand2;
    if (operation == '*') return operand1 * operand2;
    if (operation == '/') return operand1 / operand2;
    if (operation == '^') return pow(operand1, operand2);
    cout << "Unexpected Error\n";
    return -1;
}

bool IsOpenBracket(char ch)
{
    return (ch=='(' || ch=='[' || ch=='{');
}

bool IsCloseBracket(char ch)
{
    return (ch==')' || ch==']' || ch=='}');
}

char GetBracket(char c)
{
    switch (c) 
    {
        case('('): return ')';
        case(')'): return '(';
        case('['): return ']';
        case(']'): return '[';
        case('{'): return '}';
        case('}'): return '{';
    } 
    return '?'; 
}

bool IsOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

float EvaluatePostfix(string expression)
{
    stack<float> stk;
    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == ' ' || expression[i] == ',')
            continue;
        else if (IsOperator(expression[i]))
        {
            float operand2 = stk.top();
            stk.pop();
            float operand1 = stk.top();
            stk.pop();
            float result = eval(expression[i], operand1, operand2);
            stk.push(result);
        }
        else
        {
            float operand = 0;
            while (i < expression.length() && expression[i]!=' ' && expression[i]!='.')
            {
                operand = (operand * 10) + (expression[i] - '0');
                i++;
            }
            if (expression[i]=='.') 
            {
                i++;
                float p = 0.1;
                while (i < expression.length() && expression[i]!=' ')
                {
                    operand += p*(expression[i]-'0');
                    p/=10;
                    i++;
                }
            }
            stk.push(operand);
        }
    }
    return stk.top();
}

string InfixToPostfix(string infix)
{
    stack<char> operator_stack;
    stringstream output;
    bool isNumber = false;

    for (unsigned i = 0; i < infix.length(); i++)
    {
        char ch = infix[i];
        if (ch!=' ')
        {
            if (isNumber && (IsOperator(ch) || GetBracket(ch)!='?')) {
                output << " ";
                isNumber = false;
            }
            if (IsOperator(ch))
            {
                while (!operator_stack.empty() && priority(operator_stack.top()) <= priority(ch))
                {
                    output << operator_stack.top() << " ";
                    operator_stack.pop();
                }
                operator_stack.push(infix[i]);
            }
            else if (IsOpenBracket(ch))
            {
                operator_stack.push(ch);
            }
            else if (IsCloseBracket(ch))
            {
                char openBracket = GetBracket(ch);
                while (operator_stack.top() != openBracket)
                {
                    output << operator_stack.top() << " ";
                    operator_stack.pop();
                }
                operator_stack.pop();
            }
            else
            {   
                output << infix[i];
                isNumber = true;
            }
        }
    }

    if (isNumber) output << " ";
    while (!operator_stack.empty())
    {
        output << operator_stack.top() << " ";
        operator_stack.pop();
    }

    return output.str();
}

void processArgs(int argc, char **argv)
{
    string inputPath = string(argv[1]);
    int n = atoi(argv[2]);
    string action = string(argv[3]);
    string outputPath = string(argv[4]);
    
    ofstream fo;
    ifstream fi;
    string line;
    fi.open("input.txt");
    fo.open("output.txt");

    while (n--)
    {
        getline(fi, line);
        if (action == "-t")
            cout << InfixToPostfix(line) << endl;
        else
            cout << EvaluatePostfix(InfixToPostfix(line)) << endl;
    }

    fi.close();
    fo.close();
}

int main(int argc, char **argv)
{
    processArgs(argc, argv);
    return 0;
}