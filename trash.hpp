#pragma once

#include <iostream>
#include <boost/type_index.hpp> 
#include "move.hpp"
#include "forward.hpp"

#include "SuperType.hpp"

enum lifestyle
{
    GOD,
    PREDATOR,
    VICTIM
};

class Beast
{
public:
    SuperType<int> lifestyle_;

    Beast() : lifestyle_(0) {}

    template<class T>
    void set_lifestyle(T&& lifestyle)
    {
        lifestyle_ = move(lifestyle);
    }
};

void test_move_forward()
{
    start_function();

    SuperType<int> predator(PREDATOR);

    Beast lion;
    lion.set_lifestyle(predator);

    SuperType<int> victim(VICTIM);
    Beast sheep;
    sheep.set_lifestyle(victim);
    Beast cow;
    cow.set_lifestyle(victim);

    end_function();
}