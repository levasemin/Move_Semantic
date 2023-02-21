#include <iostream>
#include <string>
#include <boost/type_index.hpp>

#include "SuperType/SuperType.hpp"

template <typename T>
void func(T &&param, const std::string &param_name)
{
    using boost::typeindex::type_id_with_cvr;

    std::cout << "T: " << type_id_with_cvr<T>().pretty_name() << '\n';

    std::cout << "param: " << param_name << " is " << type_id_with_cvr<decltype(param)>().pretty_name() << "\n\n" ;
}

void test_universal_reference()
{
    SuperType<int> object_1(100500);

    func(object_1, "object_1");
    func(SuperType<int>(100500), "object_2");
}