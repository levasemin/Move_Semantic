#pragma once

#include <iostream>

#include "../SuperType/SuperType.hpp"

template<class T>
SL::SuperType<T> sum(SL::SuperType<T> a, SL::SuperType<T> b)
{
    start_function()
    
    a.rename("func_a");
    b.rename("func_b");

    SL::SuperType<int> c = a + b;
    c.rename("c");
   
    end_function()
   
    return c;
}

void test_move_semantic()
{
    start_function();
    
    SL::SuperType<int> a(5);
    a.rename("a");
    SL::SuperType<int> b(14);
    b.rename("b");
    SL::SuperType<int> c(20);
    c.rename("c");
    SL::SuperType<int> result(0);
    result.rename("result");

    result = sum(a, b * c);
    
    end_function();
}