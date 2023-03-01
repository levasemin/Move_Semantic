#pragma once

#include <iostream>
#include <string>

#include "../SuperType/SuperType.hpp"


template<class T>
void swap(T &object1, T &object2)
{    
    start_function();
    using T_ = std::remove_reference_t<T>;

    T_ temp(object1);
    temp.rename("temp");
    object1 = object2;
    object2 = temp;
    end_function();
}

void test_swap()
{
    start_function();

    SL::SuperType<int> a(10);
    a.rename("a");
    SL::SuperType<int> b(20);
    b.rename("b");
    
    swap(a, b);

    end_function();
}

