#include "Tracker.hpp"

int main()
{
    SuperType<int> a(5, "a");
    SuperType<int> b(14, "b");
    SuperType<int> c(20, "c");
    c = a + b;
}