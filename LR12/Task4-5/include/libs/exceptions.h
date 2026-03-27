#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

class Exception {
protected:
    const char* message;
public:
    Exception(const char* msg) : message(msg) {}
    const char* what() const { return message; }
};

class IndexOutOfRangeException: public Exception {
public:
    IndexOutOfRangeException() : Exception("Index of vector is out of range!") {} 
};

#endif