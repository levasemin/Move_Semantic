#pragma once

#include <iostream>
#include <string>

#include "../SuperType/SuperType.hpp"
#include "../SuperType/SL.hpp"
class Beast_2
{
public:
    SL::SuperType<std::string> lifestyle_;

    Beast_2() : lifestyle_("not_exist") {
        lifestyle_.rename("lifestyle_");
    }

    template<class T>
    void set_lifestyle(T&& lifestyle)
    {
        start_function()
        lifestyle_ = std::forward<T>(lifestyle);
        end_function()
    }
};

void test_beast_forward()
{
    start_function();

    SL::SuperType<std::string> victim("victim");

    Beast_2 lion;
    lion.set_lifestyle(SL::SuperType<std::string>("predator"));

    Beast_2 sheep;
    sheep.set_lifestyle(victim);
    Beast_2 cow;
    cow.set_lifestyle(victim);

    end_function();
}