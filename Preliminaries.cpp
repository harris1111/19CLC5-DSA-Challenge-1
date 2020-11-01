#include <iostream>
#include <stack>
using namespace std;

int priority(char ch)
{
    if (ch == '+' || ch == '-')
    {
        return 1; 
    }
    else if (ch == '*' || ch == '/')
    {
        return 2; 
    }
    else if (ch == '^')
    {
        return 3; 
    }
    else
    {
        return 0;
    }
}
bool check_Char_Is_Num(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    return false;
}
string infix_to_postfix(string infix)
{
    stack<char> S;
    S.push('#');
    string postfix = "";
    for (int i = 0; infix.length(); i++)
    {
        if (check_Char_Is_Num(char(infix[i])))
            postfix += infix[i];
        else if (infix[i] == '(')
            S.push('(');
        else if (infix[i] == '^')
            S.push('^');
        else if (infix[i] == ')')
        {
            while (S.top() != '#' && S.top() != '(')
            {
                postfix += S.top(); 
                S.pop();
            }
            S.pop();
        }
        else
        {
            if (priority(infix[i]) > priority((char)S.top()))
                S.push(infix[i]);
            else
            {
                while (S.top() != '#' && priority(infix[i]) <= priority(S.top()))
                {
                    postfix += S.top(); 
                    S.pop();
                }
                S.push(infix[i]);
            }
        }
    }
    while (S.top() != '#')
    {
        postfix += S.top();
        S.pop();
    }
    return postfix;
}
int main()
{
    string infix = "( 1 + 1 ) ^ 3";
    cout << "Postfix Form Is: " << infix_to_postfix(infix) << endl;
    system("pause");
}
