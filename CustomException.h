#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class CustomException
{
public:
    CustomException(string message)
    {
        _message = message;
    }

    string getMessage()
    {
        return _message;
    }

private:
    string _message;
};

#endif // CUSTOMEXCEPTION_H
