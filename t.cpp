#include <iostream>
#include <string>
#include <boost/type_index.hpp> 

int main()
{
    std::string a = "12345";
    using boost::typeindex::type_id_with_cvr;
    std::cout << "T ; "<< type_id_with_cvr<decltype(a)>().pretty_name() << '\n';

    std::cout <<"param ; "<<type_id_with_cvr<decltype (std::forward<decltype(a)>(a))>().pretty_name()<< '\n' ;
    
    std::string b = std::forward<decltype(a)>(a);

    static_assert(!std::is_rvalue_reference< decltype(std::forward<decltype(a)>(a)) >::value);
    
    std::string c = a;

    std::cout << "c" << c << std::endl;
    std::cout << "b" << b;
}
