#ifndef BASE_H
#define BASE_H
class Base
{
    int x;

public:
    Base();
    ~Base();
    virtual void fun() = 0;
    int getX();
};
#endif