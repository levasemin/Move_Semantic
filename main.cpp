#include "SuperInt.hpp"

int main()
{
    SuperInt<int> a(5, "a");
    SuperInt<int> b(14, "b");
    b + a;
}