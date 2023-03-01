#pragma once

#include <iostream>
#include <string>

#include "../SuperType/SuperType.hpp"
#include "../SuperType/move_forward.hpp"

class Beast_forward
{
public:
    SL::SuperType<std::string> lifestyle_;

    Beast_forward() : lifestyle_("not_exist") {
        lifestyle_.rename("lifestyle_");
    }

    template<class T>
    void set_lifestyle(T&& lifestyle)
    {
        start_function()
        lifestyle_ = SL::forward<T>(lifestyle);
        end_function()
    }
};


void test_beast_forward()
{
    start_function();

    SL::SuperType<std::string> victim("victim");

    Beast_forward lion;
    lion.set_lifestyle(SL::SuperType<std::string>("predator"));

    Beast_forward sheep;
    sheep.set_lifestyle(victim);

    Beast_forward cow;
    cow.set_lifestyle(victim);
    
    end_function();
}