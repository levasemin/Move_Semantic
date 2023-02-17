#include <iostream>
#include <boost/type_index.hpp> 

#include "SuperType.hpp"

#define start_function() Tracker::getInstance().print_open_func(__func__);
#define end_function()   Tracker::getInstance().print_close_func(__func__);

template<class T>
void swap(T &&object1, T &&object2)
{

    start_function();
    std::remove_reference_t<T> temp(object1);
    end_function();
}

template <typename T>
decltype(auto) move(T &&param)
{
    using ReturnType = std::remove_reference_t<T>&&;
    return static_cast<ReturnType>(param);
}