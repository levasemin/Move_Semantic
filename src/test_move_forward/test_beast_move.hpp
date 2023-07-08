#pragma once

#include <iostream>
#include <string>

#include "SuperType.hpp"
#include "move_forward.hpp"

class Beast_move
{
public:
    SL::SuperType<std::string> lifestyle_;

    Beast_move() : lifestyle_("not_exist") {
        lifestyle_.rename("lifestyle_");
    }

    template<class T>
    void set_lifestyle(T&& lifestyle)
    {
        start_function()
        lifestyle_ = SL::move(lifestyle);
        end_function()
    }
};


void test_beast_move()
{
    start_function();

    SL::SuperType<std::string> victim("victim");

    Beast_move lion;
    lion.set_lifestyle(SL::SuperType<std::string>("predator"));

    Beast_move sheep;
    sheep.set_lifestyle(victim);

    Beast_move cow;
    cow.set_lifestyle(victim);

    end_function();
}