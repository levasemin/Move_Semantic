#pragma once

#include <iostream>

#include "../SuperType/SuperType.hpp"

void test_rvo_rnvo()
{
    start_function()
    
    SL::SuperType<int> object_1(1);
    object_1.rename("object_1");
    SL::SuperType<int> object_2(2);
    object_2.rename("object_2");

    SL::SuperType<int> object_3 = object_1 + object_2; 
    object_3.rename("ojbect_3");

    end_function()
}