#include "expression.hpp"
#include "fraction.hpp"
#include "error.hpp"
expression::~expression()
{
        delete [] operand;
        delete [] operators;
}
expression::expression(int t, const char* A, const int* B)
{
        type = t;
        operand = new int[4];
        operators = new char[3];
        for (int i = 0 ; i < 3 ; i++)
        {
            operators[i] = A[i];
            operand[i] = B[i];
        }
        operand[3] = B[3];
}
bool expression::right()
{
    fraction a(operand[0]);
    fraction b(operand[1]);
    fraction c(operand[2]);
    fraction d(operand[3]);
    fraction res = 1;
    fraction f1 = 1;
    fraction f2 = 2;
    try
    {
        switch (type)
        {
            case 1: 
                f1 = compute(a,b,operators[0]);
                f2 = compute(c,d,operators[2]);
                res = compute(f1, f2, operators[1]);
                break;
            case 2:
                f1 = compute(a,b,operators[0]);
                f2 = compute(f1,c,operators[1]);
                res = compute(f2, d, operators[2]);
                break;   
            case 3:
                f1 = compute(b,c,operators[1]);
                f2 = compute(a,f1,operators[0]);
                res = compute(f2, d, operators[2]);
                break; 
            case 4:
                f1 = compute(b,c,operators[1]);
                f2 = compute(f1,d,operators[2]);
                res = compute(a, f2, operators[0]);
                break; 
            case 5:
                f1 = compute(c,d,operators[2]);
                f2 = compute(b,f1,operators[1]);
                res = compute(a, f2, operators[0]);
                break;   
        }
    }
    catch (error)
    { return false; }
    if (res.getval() == 24)
    { return  true; }
    return false;
}
std::ostream& operator<<(std::ostream& out, const expression& A)
{
    switch (A.type) 
    {
        case 1:
            out << '(' << A.operand[0]
                << A.operators[0] << A.operand[1] <<')'
                << A.operators[1] << '('
                << A.operand[2] << A.operators[2] 
                << A.operand[3] << ')';
            break;
        case 2:
            out << '[' << '('
                << A.operand[0] << A.operators[0]
                << A.operand[1] << ')'
                << A.operators[1] << A.operand[2] << ']'
                << A.operators[2] << A.operand[3]; 
            break;
        case 3:
            out << '[' << A.operand[0] << A.operators[0]
                << '('
                << A.operand[1] << A.operators[1] << A.operand[2] << ')' << ']'
                << A.operators[2] << A.operand[3]; 
                break;
        case 4:
            out << A.operand[0] << A.operators[0]
                << '[' << '(' << A.operand[1]
                << A.operators[1] << A.operand[2] << ')'
                << A.operators[2] << A.operand[3] << ']'; 
                break;
        case 5:
            out << A.operand[0] << A.operators[0]
                << '[' << A.operand[1] << A.operators[1] 
                << '('  << A.operand[2] << A.operators[2]
                << A.operand[3] << ')' << ']'; 
                break;
    }
    return out;
}