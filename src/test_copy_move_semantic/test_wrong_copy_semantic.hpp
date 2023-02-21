#include <iostream>
#include <string>

#include "../SuperType/SuperType.hpp"


void test_wrong_copy_constructor()
{
    const SL::SuperType<int> c(20);
    SL::SuperType<int> result(c);    
}


void test_wrong_copy_operator()
{
    const SL::SuperType<int> c(20);
    SL::SuperType<int> result(0);
    
    result = c;
}