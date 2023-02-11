#include "SuperType.hpp"
          
#define start_function() Tracker::getInstance().print_open_func(__func__);
#define end_function()   Tracker::getInstance().print_close_func(__func__);


template<class T>
SuperType<T> func1(SuperType<T> a, SuperType<T> b)
{
    start_function()
    SuperType<int> c = a + b;
    end_function()
    return c;
}

template<class T>
SuperType<T> func2(SuperType<T> a, SuperType<T> b)
{
    start_function()
    SuperType<int> c = a + b;
    end_function()
    return c;
}

int main()
{
    start_function();
    SuperType<int> a(5, "a");
    SuperType<int> b(14, "b");
    SuperType<int> c1(func1(a, b), "c1");
    SuperType<int> c2(func2(a, b), "c2");
    SuperType<float> c3(0.5, "c3");
    end_function();
}