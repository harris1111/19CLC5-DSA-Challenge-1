#include <iostream>
#include <sstream>
#include <stack>
#include <limits>
#include <string>
#include <cmath>
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
    for (int i = 0; i < expression.length(); i++)
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
int main()
{
    string infix;
    getline(cin, infix);

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
        else if (infix[i] == '(')
        {
            operator_stack.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (operator_stack.top() != '(')
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

    cout << output.str() << endl;
    cout << EvaluatePostfix(output.str()) << endl;
    system("pause");

    return 0;
}