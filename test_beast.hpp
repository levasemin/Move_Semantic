#include "SuperType.hpp"

#ifndef BEAST_FORWARD
class Beast
{
public:
    SuperType<std::string> lifestyle_;

    Beast() : lifestyle_("not_exist") {
        lifestyle_.rename("lifestyle_");
    }

    template<class T>
    void set_lifestyle(T&& lifestyle)
    {
        start_function()
        lifestyle_ = std::move(lifestyle);
        end_function()
    }
};
#endif 

#ifdef BEAST_FORWARD
class Beast
{
public:
    SuperType<std::string> lifestyle_;

    Beast() : lifestyle_("not_exist") {
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
#endif 

void test_beast()
{
    start_function();

    SuperType<std::string> victim("victim");

    Beast lion;
    lion.set_lifestyle(SuperType<std::string>("predator"));

    Beast sheep;
    sheep.set_lifestyle(victim);
    Beast cow;
    cow.set_lifestyle(victim);

    end_function();
}