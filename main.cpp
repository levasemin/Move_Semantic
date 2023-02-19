//TODO: 
//check type of object for choose his color, solution is not ""

#include "SuperType.hpp"
          
#define start_function() Tracker::getInstance().print_open_func(__func__);
#define end_function()   Tracker::getInstance().print_close_func(__func__);


template<class T>
SuperType<T> func(SuperType<T> a, SuperType<T> b)
{
    start_function()
    SuperType<int> c = a + b;
    // c.rename("c");
    end_function()
    return c;
}

int main()
{
    start_function();
    
    SuperType<int> a(5);
    SuperType<int> b(14);
    SuperType<int> c(20);
    SuperType<int> result(0, "result");
    
    result = c;
    result = func(a, b * c);
    
    end_function();
}