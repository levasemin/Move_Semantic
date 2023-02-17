#include <iostream>
#include <string>
#include <boost/type_index.hpp> 

class Object
{
public:
    
    int value_;

    Object(int value)
    {
        value_ = value;
    }
};

template<typename T>
void doSomething(T&& this_) 
{
    if(std::is_rvalue_reference<T&&>::value) 
    {
        std::cout << "YEAH" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }
}

template<class T1, class T2>
Object &operator +=(T1&& object1, T2&& object2)
{
    object1.value_ += object2.value_;

    return object1;
}

template<class T1, class T2>
Object operator +(T1&& object1, T2&& object2)
{
    if(std::is_rvalue_reference<T1&&>::value) 
    {
        std::cout << "YEAH" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }

    if(std::is_rvalue_reference<T2&&>::value) 
    {
        std::cout << "YEAH" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }

    std::remove_reference_t<T2> result = object1;
    result += object2;

    return result;
}

int main()
{
    Object c(5);
    c + Object(6);
}
