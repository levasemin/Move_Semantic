#include "SuperType.hpp"

template<class T>
SuperType<T> func(SuperType<T> a, SuperType<T> b)
{
    a.rename("func_a");
    b.rename("func_b");
    start_function()
    SuperType<int> c = a + b;
    c.rename("c");
    end_function()
    return c;
}

void test_move_semantic()
{
    start_function();
    
    SuperType<int> a(5);
    a.rename("a");
    SuperType<int> b(14);
    b.rename("b");
    SuperType<int> c(20);
    c.rename("c");
    SuperType<int> result(0);
    result.rename("result");

    result = c;
    result = func(a, b * c);
    
    end_function();
}