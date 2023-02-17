#include "SuperType.hpp"
#include "functions.hpp"

void func(SuperType<int> &a)
{
    start_function();
    SuperType<int> temp(a);
    end_function();
}

int main()
{
    start_function();

    SuperType<int> a(5, "a");
    SuperType<int> b(6, "b");

    func(a);
    
    end_function()
}