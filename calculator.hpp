#ifndef CALCULATOR
#define CALCULATOR
#include <cmath>
#include <string>
#include <iostream>
#include <stack>
#include "error.hpp"
#include "fraction.hpp"
using std::string, std::cin, std::stack;
class calculator  
{
    public:
    string context;
    calculator()=default;
    void read(const string& a)
    {
        context = a;
    }
    void fun(stack<char>& s, stack<fraction>& num)
    {
        char x = s.top();
        s.pop();
        auto op1 = num.top();
        num.pop();
        auto op2 = num.top();
        num.pop();
        auto res = compute(op2, op1, x);
        num.push(res);
    }
    fraction result()
    {
        stack<char> s;
        stack<fraction> num;
        auto it = context.begin();
        do 
        {
            switch (*it) 
            {
                case ' ':
                { 
                    it++;
                    break; 
                }
                case '*': case '/':
                {
                    if (!s.empty())
                    {
                        while (
                            !s.empty() &&
                            (s.top() == '+' || 
                            s.top() == '-' ||
                            s.top() == '*' ||
                            s.top() == '/') )
                        { fun(s, num); }
                        s.push(*it);
                    }
                    else  
                    { s.push(*it); }
                    it++;
                    break;
                }
                case ')':
                {
                    while (s.top() != '(')
                    { fun(s, num); }
                    s.pop();
                    it++;
                    break;
                }
                case '(':
                {
                    s.push(*it);
                    it++;
                    break;
                }
                case '+': case '-':
                {
                    if (!s.empty())
                    {
                        while (
                            !s.empty() &&
                            (s.top() == '+' || 
                            s.top() == '-') )
                        { fun(s, num); }
                        s.push(*it);
                    }
                    else  
                    { s.push(*it); }
                    it++;
                    break;
                }
                default: 
                {
                    string x;
                    while (*it >= '0' && *it <= '9' && it != context.end())
                    { 
                        x += *it;
                        it++;
                    }
                    num.push(std::stoi(x));
                }
            }
        }
        while (it != context.end() );
        while (num.size() > 1 && s.size() > 0)
        { fun(s, num); }
        if (num.size() != 1 || s.size() != 0)
        { throw error("calculate error"); }
        return num.top();
    }
};

#endif