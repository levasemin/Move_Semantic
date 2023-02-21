#pragma once

#include <iostream>
#include <string>

#include "SuperType.hpp"


template<class T>
void swap_default(T &&object1, T &&object2)
{    
    start_function();
    using T_ = std::remove_reference_t<T>;

    T_ temp(object1);
    temp.rename("temp");
    object1 = object2;
    object2 = temp;
    end_function();
}

void test_swap_default()
{
    start_function();

    SuperType<int> a(10);
    a.rename("a");
    SuperType<int> b(20);
    b.rename("b");
    
    swap_default(dynamic_cast<SuperType<int> &&>(a), dynamic_cast<SuperType<int> &&>(b));

    end_function();
}

