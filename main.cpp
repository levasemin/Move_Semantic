#include "test_move_forward.hpp"
#include "test_move_semantic.hpp"
#include "test_wrong_copy_semantic.hpp"

void start_test(const char *type)
{
    if (type == std::string("test_move_semantic"))
    {
        test_move_semantic();
    }

    else if (type == std::string("test_move_forward"))
    {
        test_move_forward();
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