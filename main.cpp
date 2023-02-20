#include "test_move_semantic.hpp"
#include "test_wrong_copy_semantic.hpp"
#include "test_swap.hpp"
#include "test_beast.hpp"

void start_test(const char *type)
{
    if (type == std::string("test_move_semantic"))
    {
        test_move_semantic();
    }

    else if (type == std::string("test_swap"))
    {
        test_swap();
    }

    else if (type == std::string("test_beast"))
    {
        test_beast();
    }
}

int main(int argc, char *argv[])
{   
    switch(argc)
    {
        case 2:
        {
            Tracker &tracker = Tracker::getInstance();
            tracker.open_file("graph.dot");

            start_test(argv[1]);            

            break;
        }

        case 3:        
        {
            Tracker &tracker = Tracker::getInstance();
            tracker.open_file(argv[2]);
            
            start_test(argv[1]);
            
            break;
        }

        default:
        {
            Tracker &tracker = Tracker::getInstance();
            tracker.open_file("graph.dot");
            
            test_move_semantic();
            
            break;
        }
    }


}