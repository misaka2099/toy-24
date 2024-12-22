#ifndef FRACTION
#define FRACTION

class fraction 
{
    int denominator;
    int numerator;
    public:
    ~fraction()=default;
    fraction(int a, int b = 1);
    void simplify();
    
    friend fraction operator+(const fraction& A, const fraction& B);
    friend fraction operator-(const fraction& A, const fraction& B); 
    friend fraction operator*(const fraction& A, const fraction& B);
    friend fraction operator/(const fraction& A, const fraction& B);
    double getval();
    friend fraction compute(const fraction& A, const fraction& B, const char& C);
};

#endif