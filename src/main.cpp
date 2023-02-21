#include "test_copy_move_semantic/test_move_semantic.hpp"
#include "test_copy_move_semantic/test_wrong_copy_semantic.hpp"
#include "test_move_forward/test_swap_default.hpp"
#include "test_move_forward/test_swap_move.hpp"
#include "test_move_forward/test_beast_move.hpp"
#include "test_move_forward/test_beast_forward.hpp"
#include "test_universal_reference/universal_reference.hpp"

void start_test(const std::string &type)
{
    if (type == "test_move_semantic")
    {
        test_move_semantic();
    }

    else if (type == "test_swap_deafult")
    {
        test_swap_default();
    }

    else if (type == "test_swap_move")
    {
        test_swap_move();
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
            Tracker &tracker = Tracker::getInstance();
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