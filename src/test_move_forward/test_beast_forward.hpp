#include <iostream>
#include <string>

#include "SuperType.hpp"
#include "SuperType/forward.hpp"
class Beast_2
{
public:
    SuperType<std::string> lifestyle_;

    Beast_2() : lifestyle_("not_exist") {
        lifestyle_.rename("lifestyle_");
    }

    template<class T>
    void set_lifestyle(T&& lifestyle)
    {
        start_function()
        lifestyle_ = forward<T>(lifestyle);
        end_function()
    }
};

void test_beast_forward()
{
    start_function();

    SuperType<std::string> victim("victim");

    Beast_2 lion;
    lion.set_lifestyle(SuperType<std::string>("predator"));

    Beast_2 sheep;
    sheep.set_lifestyle(victim);
    Beast_2 cow;
    cow.set_lifestyle(victim);

    end_function();
}