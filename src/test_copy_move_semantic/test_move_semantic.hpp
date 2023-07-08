#pragma once

#include <iostream>

#include "SuperType.hpp"

template<class T>
SL::SuperType<T> 
sum(SL::SuperType<T> a, SL::SuperType<T> b)
{
    start_function();             // начало функции для трекинга
    
    a.rename("func_a");           // переименование узла объекта
    b.rename("func_b");           // переименование узла объекта

    SL::SuperType<int> c = a + b;
    c.rename("c");                // переименование узла объекта
   
    end_function();               // конец функции для трекинга
   
    return c;
}

void test_move_semantic()
{
    start_function();             // начало функции для трекинга
    
    SL::SuperType<int> a(5);
    a.rename("a");                // переименование узла объекта
    SL::SuperType<int> b(14);
    b.rename("b");                // переименование узла объекта
    SL::SuperType<int> c(20);
    c.rename("c");                // переименование узла объекта
    SL::SuperType<int> result(0);
    result.rename("result");      // переименование узла объекта

    result = sum(a, b * c);
    
    end_function();               // конец функции для трекинга
}