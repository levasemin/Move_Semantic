#pragma once

#include <iostream>
#include <boost/type_index.hpp> 
#include "move.hpp"
#include "forward.hpp"

#include "SuperType.hpp"

#ifdef SWAP_MOVE
template<class T>
void swap(T &&object1, T &&object2)
{    
    start_function();
    using T_ = std::remove_reference_t<T>;

    T_ temp(move(object1));
    temp.rename("temp");
    object1 = move(object2);
    object2 = move(temp);
    end_function();
}
#endif

#ifndef SWAP_MOVE
template<class T>
void swap(T &&object1, T &&object2)
{    
    start_function();
    using T_ = std::remove_reference_t<T>;

    T_ temp(object1);
    temp.rename("temp");
    object1 = object2;
    object2 = temp;
    end_function();
}
#endif

void test_swap()
{
    start_function();

    SuperType<int> a(10);
    a.rename("a");
    SuperType<int> b(20);
    b.rename("b");

    swap(a, b);

    end_function();
}
