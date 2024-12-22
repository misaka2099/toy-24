#ifndef EXPRESSION 
#define EXPRESSION

/* type
1 (AB)(CD)
2 [(AB)C]D
3 [A(BC)]D
4 A[(BC)D]
5 A[B(CD)]
*/
/* operator
1 +
2 -
3 *
4 /
*/ 
#include <ostream>

class expression
{
    int type;
    char* operators;
    int* operand;
    public:
    ~expression();
    expression(int t, const char* A, const int* B);
    bool right();
    friend std::ostream& operator<<(std::ostream& out, const expression& A); 
};
#endif