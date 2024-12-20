#include "varify.hpp"
#include "expression.hpp"
#include <map>
#include <stack>
#include <string>
#include "data.hpp"

bool indata(int arr[])
{
    std::map<int, int> a;
    for (int i = 0 ; i < 4 ; i++)
    { a[data[i]] = 0; }
    for (int i = 0 ; i < 4 ; i++)
    { a[data[i]]++; }
    for (int i = 0 ; i < 4 ; i++)
    { 
        if (a.find(arr[i]) == a.end())
        { return false; }
        a[arr[i]]--;
        if (a[arr[i]] < 0)
        { return false;}
    }
    return true;
}
bool legal(const std::string& a)
{
    int num = 0;
    int op = 0;
    int arr[4];
    std::stack<char> s;
    auto it = a.begin();
    while (it != a.end()) 
    {
        switch (*it) 
        {
            case ' ':
            { break; }
            case '(':
            {
                s.push(*it);
                break;
            }
            case ')':
            {
                if (s.empty())
                { return false; }
                s.pop();
                break;
            }
            case '+': case '-': case '*': case '/':
            { 
                op++;
                if (op > 3)
                { return false; }
                break;
            }
            default:
            {
                if (*it < '0' || *it > '9' )
                { return false;; }
                else 
                {
                    std::string x;
                    while (*it >= '0' && *it <= '9' && it != a.end())
                    { 
                        x += *it;
                        it++;
                    }
                    if (num == 4)
                    { return false;}
                    arr[num] = stoi(x);
                    it--;
                    num++;
                }
            }
        }
        it++;
    }
    if (indata(arr))
    { return true; }
    return false;
}
void GenerateData()
{
    std::srand(time(0));
    for (int i = 0 ; i <= 3 ; i++)
    { data[i] = rand() % 13 + 1; }
}
bool exist()
{
    for (int i = 0 ; i < 4 ; i++)
    {
        for (int j = 0 ; j < 4 ; j++)
        {
            if (j == i)
            { continue; }
            for (int k = 0 ; k < 4 ; k++)
            {
                if (k == j || k == i)
                { continue; }
                for (int l = 0 ; l < 4 ; l++)
                {
                    if (l == j || l == i || l == k)
                    { continue; }
                    for (int op1 = 0 ; op1 < 4 ; op1++)
                    {
                        for (int op2 = 0 ; op2 < 4 ; op2++)
                        {
                            
                            for (int op3 = 0 ; op3 < 4 ; op3++)
                            {
                                for (int type = 1 ; type <= 5 ; type++)
                                {
                                    int arr[]={data[i],data[j],data[k],data[l]};
                                    char ops[]={op[op1], op[op2], op[op3]};
                                    expression res(type, ops, arr);
                                    if (res.right())
                                    { 
                                        ans.str("");
                                        ans << res;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}