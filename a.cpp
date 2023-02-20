#include <iostream>
#include <string>

int main()
{
    std::string a = "1234"; 
    std::string b = "5678";
    std::string c = "9101";

    a = std::move(b);
    c = std::move(b);
    std::cout << "a " << a;
    std::cout << "b " << b;
}