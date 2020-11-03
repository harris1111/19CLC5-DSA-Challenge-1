/*
    This is my team's implement how infix to postfix algorithm work in C/C++
*/
#include <sstream> // using stringstream
#include <stack>   // for using stack
#include <string>  // using string type
#include <string.h>
#include <cmath>   // using pow fucntion
#include <fstream> // for file handling
using namespace std;

/*
    This function will return the priority of each element in the expression
    In this case, ^ first, * / is second and third is +, -
    Other stuff like ( ), { }, [ ], is 4, which is final. 
*/
int priority(char a)
{
    if (a == '^')
        return 1;
    if (a == '*' || a == '/')
        return 2;
    if (a == '+' || a == '-')
        return 3;
    return 4;
}
/*
    This function return the value of operands and operators
*/
float eval(char operation, float operand1, float operand2)
{
    if (operation == '+')
        return operand1 + operand2;
    if (operation == '-')
        return operand1 - operand2;
    if (operation == '*')
        return operand1 * operand2;
    if (operation == '/')
        return operand1 / operand2;
    if (operation == '^')
        return pow(operand1, operand2);
    return -1;
}

//check whether the give char is an open bracket or not
bool IsOpenBracket(char ch)
{
    return (ch == '(' || ch == '[' || ch == '{');
}

//check whether the give char is an close bracket or not
bool IsCloseBracket(char ch)
{
    return (ch == ')' || ch == ']' || ch == '}');
}

//get close bracket if the given char is open bracket
char GetBracket(char c)
{
    switch (c)
    {
    case ('('):
        return ')';
    case (')'):
        return '(';
    case ('['):
        return ']';
    case (']'):
        return '[';
    case ('{'):
        return '}';
    case ('}'):
        return '{';
    }
    return '?';
}

//check whether the given char is operator or not
bool IsOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

/*
    This function will implement how to calculate the value of postfix
    1) Create a stack to store operands (or values).
    2) Scan the given expression and do following for every scanned element.
        …..a) If the element is a number, push it into the stack
        …..b) If the element is a operator, pop operands for the operator from stack. 
              Evaluate the operator and push the result back to the stack
    3) When the expression is ended, the number in the stack is the final answer
*/
float EvaluatePostfix(string expression)
{
    stack<float> stk; //creating a stack to store float value
    for (int i = 0; i < expression.length(); i++)
    {
        if (expression[i] == ' ') // skip ' ' to calculate the exact value
            continue;
        //If this char is Operator, do the operator
        else if (IsOperator(expression[i]))  
        {
            //take the first operand
            float operand2 = stk.top();
            stk.pop();
            //take the second operand
            float operand1 = stk.top();
            stk.pop();
            //evaluate the operator
            float result = eval(expression[i], operand1, operand2);
            stk.push(result);
        }
        else
        {
            /*
                Because of the input type is float with maximum 2 digit after the comma
                So the algorithm here, is:
                 - if the number is not float, we take the digit until we meet " "
                 and then we use the algorithm below to calc.
            */
            float operand = 0;
            while (i < expression.length() && expression[i] != ' ' && expression[i] != '.')
            {
                operand = (operand * 10) + (expression[i] - '0');
                i++;
            }
            /*
                If we meet float number, we will get digit and iterate until we meet ' '
                The tithes will follow the formula: a[0]*10^-1 + a[1]*10^-2 + ... + a[n]*10^-(n+1)
            */
            if (expression[i] == '.')
            {
                i++;
                float p = 0.1;
                while (i < expression.length() && expression[i] != ' ')
                {
                    operand += p * (expression[i] - '0');
                    p /= 10;
                    i++;
                }
            }
            stk.push(operand);
        }
    }
    return stk.top();
}
/*
    This function implement how to convert infix to postfix
*/
string InfixToPostfix(string infix)
{
    stack<char> operator_stack; // creating operator_stack to store operator
    stringstream output; // store postfix output
    bool isNumber = false; // check whether the char is a digit or not

    for (unsigned i = 0; i < infix.length(); i++)
    {
        char ch = infix[i];
        //skip ' '
        if (ch != ' ')
        {
            //if this element is a valid (operand, operator, open/close bracket)
            //input ' ' for right format output
            if (isNumber && (IsOperator(ch) || GetBracket(ch) != '?'))
            {
                output << " ";
                isNumber = false;
            }
            //if this element is Operator
            if (IsOperator(ch))
            {
                while (!operator_stack.empty() && priority(operator_stack.top()) <= priority(ch))
                {
                    //pop the element which has higher priority
                    output << operator_stack.top() << " ";
                    operator_stack.pop();
                }
                operator_stack.push(infix[i]);
            }
            /*
                process Open and Close Bracket
            */
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
    //add " " to digit for tight output
    if (isNumber)
        output << " ";
    //add the rest of the expression
    while (!operator_stack.empty())
    {
        output << operator_stack.top() << " ";
        operator_stack.pop();
    }
    return output.str();
}
/*
    This function return the validity of the expression
*/
bool valid(string line)
{
    stack<char> stk;
    bool number = false;
    for (int i = 0; i < line.length(); i++)
    {
        char ch = line[i];
        //check if open and close bracket is at the right position
        if (IsOpenBracket(ch))
        {
            stk.push(ch);
        }
        else if (IsCloseBracket(ch))
        {
            if (stk.empty() || stk.top() != GetBracket(ch))
                return false;
            stk.pop();
        }
        //check if the element is operator
        else if (IsOperator(ch))
        {
            number = false;
        }
        //skip ' '
        else if (ch != ' ')
        {
            if (number)
                return false;
            //check digit or '.' of float;
            while (i < line.length() && ((line[i] <= '9' && line[i] >= '0') || line[i] == '.'))
            {
                i++;
            }
            i--;
            number = true;
        }
    }
    return true;
}
//This function process argument value to use in commandline
void processArgs(int argc, char **argv)
{
    string inputPath = string(argv[1]);
    int n = atoi(argv[2]);
    string action = string(argv[3]);
    string outputPath = string(argv[4]);
    ofstream fo;
    ifstream fi;
    string line;
    fi.open(inputPath);
    fo.open(outputPath);
    while (n--)
    {
        getline(fi, line);
        if (!valid(line))
        {
            fo << "E\n";
            continue;
        }
        if (action == "-t")
            fo << InfixToPostfix(line) << endl;
        else
            fo << EvaluatePostfix(InfixToPostfix(line)) << endl;
    }
    fi.close();
    fo.close();
}
//Main driver
int main(int argc, char **argv)
{
    processArgs(argc, argv);
    system("pause");
    return 0;
}