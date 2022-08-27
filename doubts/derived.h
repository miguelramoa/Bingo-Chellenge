#ifndef DERIVED_H
#define DERIVED_H
#include "base.h"
#include "base.cpp"
class Derived : public Base
{
    int y;

public:
    Derived();
    ~Derived();
    void fun();
};
#endif