#include "SuperType.hpp"

void test_wrong_copy_constructor()
{
    const SuperType<int> c(20);
    SuperType<int> result(c);    
}


void test_wrong_copy_operator()
{
    const SuperType<int> c(20);
    SuperType<int> result(0);
    
    result = c;
}