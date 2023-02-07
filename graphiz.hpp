#include<fstream>
#include<string>

#include "SuperInt.hpp"

//     m1[xlabel=mblk_t label="<h> m1 | <p> *prev |<n> *next |<c> *cont |<d> *data | other\nstuff" ];;

void create_file(std::ofstream &file, const std::string &name);

void close_file(std::ofstream &file);

void print_operation(std::ofstream &file, const std::string &operation);