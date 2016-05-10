#ifndef EOFEXCEPTION_H
#define EOFEXCEPTION_H

#include <exception>

class EOFexception : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "End of file";
    }
};

#endif