#include <iostream>
#include <string>
#include <boost/type_index.hpp> 

template <class T>
class Object
{
public:
    
    int value_;

    Object(int value)
    {
        value_ = value;
    }
};

template<class T1, class T2>
std::remove_reference_t<T1> &operator +=(T1&& object1, T2&& object2)
{
    object1.value_ += object2.value_;

    return object1;
}

template<class T1, class T2>
std::remove_reference_t<T1> operator +(T1&& object1, T2&& object2)
{
    if(std::is_rvalue_reference<T1&&>::value) 
    {
        std::cout << "Object1 is rvalue" << std::endl;
    }
    else
    {
        std::cout << "Object1 is lvalue" << std::endl;
    }

    if(std::is_rvalue_reference<T2&&>::value) 
    {
        std::cout << "Object2 is rvalue" << std::endl;
    }
    else
    {
        std::cout << "Object2 is lvalue" << std::endl;
    }

    std::remove_reference_t<T2> result = object1;
    result += object2;

    return result;
}

int main()
{
    Object<int> c(5);
    c + Object<int>(6);
}
