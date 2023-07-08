#pragma once

#include <iostream>

#include "SuperType.hpp"

template<class T>
SL::SuperType<T> sum_naked(SL::SuperType<T> a, SL::SuperType<T> b)
{
    SL::SuperType<int> c = a + b;
      
    return c;
}

void test_move_semantic_naked()
{    
    SL::SuperType<int> a(5);
    SL::SuperType<int> b(14);
    SL::SuperType<int> c(20);
    SL::SuperType<int> result(0);

    result = sum_naked(a, b * c);
}