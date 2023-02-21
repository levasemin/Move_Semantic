#pragma once

#include <iostream>
#include <string>

#include "SuperType.hpp"
#include "SuperType/move.hpp"

template<class T>
void swap_move(T &&object1, T &&object2)
{    
    start_function();
    using T_ = std::remove_reference_t<T>;

    T_ temp(move(object1));
    temp.rename("temp");
    object1 = move(object2);
    object2 = move(temp);
    end_function();
}

void test_swap_move()
{
    start_function();

    SuperType<int> a(10);
    a.rename("a");
    SuperType<int> b(20);
    b.rename("b");

    swap_move(a, b);

    end_function();
}

