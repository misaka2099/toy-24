#include "fraction.hpp"
#include "error.hpp"
#include <cstdlib>
#include <numeric>

fraction::fraction(int a, int b)
{
    if (b == 0)
    { throw error("divide_by_zero"); }
    numerator = a;
    denominator = b;
}
void fraction::simplify()
{
    int gcd = std::gcd(abs(denominator),abs(numerator));
    numerator /= gcd;
    denominator /= gcd;
}
fraction operator+(const fraction& A, const fraction& B)
{
    int num = A.numerator * B.denominator + B.numerator * A.denominator;
    int den = A.denominator * B.denominator;
    fraction res(num, den);
    res.simplify();
    return res;
}
fraction operator-(const fraction& A, const fraction& B)
{
    int num = A.numerator * B.denominator - B.numerator * A.denominator;
    int den = A.denominator * B.denominator;
    fraction res(num, den);
    res.simplify();
    return res;
}
fraction operator*(const fraction& A, const fraction& B)
{
    int num = B.numerator * A.numerator;
    int den = A.denominator * B.denominator;
    fraction res(num, den);
    res.simplify();
    return res;
}
fraction operator/(const fraction& A, const fraction& B)
{
    if (B.numerator == 0)
    { throw error("divide_by_zero"); }
    int num = A.numerator * B.denominator;
    int den = A.denominator * B.numerator;
    fraction res(num, den);
    res.simplify();
    return res;
}
double fraction::getval()
{ return double(numerator)/denominator; }
fraction compute(const fraction& A, const fraction& B, const char& C)
{
    fraction res = 1;
    switch (C)
    {
        case '+': 
            res = A + B;
            break;
        case '-':
            res = A - B;
            break;
        case '*':
            res = A * B;
            break;
        case '/':
            res = A / B;
            break;
    }
    return res;

}