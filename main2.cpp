#include "SuperType.hpp"
#include "functions.hpp"

int main()
{
    SuperType<int> a(5);
    a.rename("a");
    SuperType<int> b(10);   
    b.rename("b");
    
    swap(a, b);
}