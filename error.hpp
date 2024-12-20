#ifndef ERROR
#define ERROR
#include<string>
class error
{
    const std::string x;
    public:
    error(const std::string& other): x(other)
    {}
    std::string show()
    { return x; }
};
#endif