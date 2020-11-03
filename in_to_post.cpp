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
    int temp;
    if (a == '^')
        temp = 1;
    else if (a == '*' || a == '/')
        temp = 2;
    else if (a == '+' || a == '-')
        temp = 3;
    return temp;
}
long eval(char operation, int operand1, int operand2)
{
    if (operation == '+')
        return operand1 + operand2;
    else if (operation == '-')
        return operand1 - operand2;
    else if (operation == '*')
        return operand1 * operand2;
    else if (operation == '/')
        return operand1 / operand2;
    else if (operation == '^')
        return pow(operand1, operand2);
    else
        cout << "Unexpected Error \n";
    return -1;
}
bool IsOperator(char C)
{
    if (C == '+' || C == '-' || C == '*' || C == '/' || C == '^')
        return true;
    return false;
}
int EvaluatePostfix(string expression)
{
    stack<int> S;
    for (unsigned int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == ' ' || expression[i] == ',')
            continue;

        else if (IsOperator(expression[i]))
        {
            int operand2 = S.top();
            S.pop();
            int operand1 = S.top();
            S.pop();
            int result = eval(expression[i], operand1, operand2);
            S.push(result);
        }
        else if (isdigit(expression[i]))
        {
            int operand = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                operand = (operand * 10) + (expression[i] - '0');
                i++;
            }
            i--;
            S.push(operand);
        }
    }
    return S.top();
}
string in_to_post(string infix)
{
    stack<char> operator_stack;

    stringstream output;

    for (unsigned i = 0; i < infix.length(); i++)
    {
        if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^')
        {
            while (!operator_stack.empty() && priority(operator_stack.top()) <= priority(infix[i]))
            {
                output << operator_stack.top();
                operator_stack.pop();
            }
            operator_stack.push(infix[i]);
        }
        else if ((infix[i] == '(') && (infix[i] == '[') && (infix[i] == '{'))
        {
            operator_stack.push(infix[i]);
        }
        else if ((infix[i] == ')') && (infix[i] == ']') && (infix[i] == '}'))
        {
            while ((operator_stack.top() != '(') && (operator_stack.top() != '[') && (operator_stack.top() != '{'))
            {
                output << operator_stack.top();
                operator_stack.pop();
            }
            operator_stack.pop();
        }
        else
        {
            output << infix[i];
        }
    }

    while (!operator_stack.empty())
    {
        output << operator_stack.top();
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
    while (fi >>line)
    {
        getline(fi, line, '\n');
        // if (action == "-t")
        //     fo << in_to_post(line) << endl;
        // if (action == "-c")
        //     fo << EvaluatePostfix(in_to_post(line)) << endl;
        // i++;
        cout << line << endl;
    }
    fi.close();
    fo.close();
}
int main(int argc, char **argv)
{
    processArgs(argc, argv);
    system("pause");
    return 0;
}