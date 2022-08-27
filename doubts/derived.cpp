#include <iostream>
#include "derived.h"

Derived::Derived()
{
    std::cout << "Criando" << std::endl;
}
Derived::~Derived(){

}
void Derived::fun()
{
    std::cout << "fun() called";
}