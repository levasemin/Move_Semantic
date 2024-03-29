#include "test_move_semantic_naked.hpp"
#include "test_move_semantic.hpp"
#include "test_rvo_rnvo.hpp"
#include "test_swap.hpp"
#include "test_swap_move.hpp"
#include "test_beast.hpp"
#include "test_beast_move.hpp"
#include "test_beast_forward.hpp"
#include "universal_reference.hpp"

void start_test(const std::string &type)
{
    if (type == "test_move_semantic_naked")
    {
        test_move_semantic_naked();
    }

    else if (type == "test_move_semantic")
    {
        test_move_semantic();
    }
    
    else if (type == "test_rvo_rnvo")
    {
        test_rvo_rnvo();
    }

    else if (type == "test_swap")
    {
        test_swap();
    }

    else if (type == "test_swap_move")
    {
        test_swap_move();
    }

    else if (type == "test_beast")
    {
        test_beast();
    }

    else if (type == "test_beast_move")
    {
        test_beast_move();
    }

    else if (type == "test_beast_forward")
    {
        test_beast_forward();
    }

    else if (type == "test_universal_reference")
    {
        test_universal_reference();
    }
}

int main(int argc, char *argv[])
{   
    switch(argc)
    {
        case 3:        
        {
            SL::Tracker &tracker = SL::Tracker::getInstance();
            tracker.open_file(argv[2]);
            
            start_test(argv[1]);
            
            break;
        }

        case 2:
        {
            start_test(argv[1]);
            
            break;
        }

        default:
        {   
            break;
        }
    }
}