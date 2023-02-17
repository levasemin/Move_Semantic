#pragma once
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
template <class T>


class SuperType;

 enum OPERATIONS
{
    MONO_ADD,
    MONO_SUB,
    MONO_MUL,
    MONO_DIV,
    MONO_MOD,
    MONO_AND,
    MONO_OR,
    MONO_DEGREE,
    BIN_ADD,
    BIN_SUB,
    BIN_MUL,
    BIN_DIV,
    BIN_MOD,
    BIN_BIT_AND,
    BIN_BIT_OR,
    BIN_DEGREE,
    EQ_COPY,
    EQ_MOVE,
    CONSTRUCTOR_COPY,
    CONSTRUCTOR_MOVE
};

class Tracker
{
public:
    static Tracker &getInstance()
    {
        static Tracker tracker;
        return tracker;
    }

    std::vector<std::string> operations_ = {"+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "+", "-", "*", "/", "%", "&", "|", "^", "= (copy)", "= (move)", "copy", "move"};

    template <class T>
    void print_operation(const SuperType<T> &first_object, const SuperType<T> &second_object, SuperType<T> &result, OPERATIONS operation, 
                         const std::string &color = "black", const std::string &style = "");

    template<class T>
    int print_operation(SuperType<T> &first_object, OPERATIONS operation, const std::string &color = "black", const std::string &style = "");

    int print_oper(OPERATIONS operation, const std::string &color = "black", const std::string &style = "");

    template<class T>
    void print_node(SuperType<T> &object);

    void print_edge(int id1, int id2);
    
    void print_open_func(const std::string &name);

    void print_close_func(const std::string &name);

    void create_file(const std::string &file_name);

    void close_file();

private:

    std::ofstream file_;
    std::string file_name_;

    int func_id = 0;
    int id = 0;

    int copy_count_ = 0;
    int move_count_ = 0;
    
    Tracker(const std::string &file_name = "graph.dot") : 
        file_name_(file_name),
        file_()
    {
        file_name_.erase(file_name_.end()-4, file_name_.end());
        create_file(file_name);
    }

    ~Tracker()
    {
        file_ << "label=\"Count of copy operation: " << copy_count_ << "\n" << "Count of move operation: " << move_count_ << "\"";
        close_file();
    }

    Tracker(const Tracker&);
    Tracker& operator=(const Tracker&);
};


template <class T>
void Tracker::print_operation(const SuperType<T> &first_object, const SuperType<T> &second_object, SuperType<T> &result, OPERATIONS operation, 
                        const std::string &color, const std::string &style)
{
    print_oper(operation, color, style);
    int operation_id = id;

    print_edge(first_object.id_, operation_id);
    print_edge(second_object.id_, operation_id);
    result.id_ = -1;
    print_node(result);
    print_edge(operation_id, result.id_);
}

template<class T>
int Tracker::print_operation(SuperType<T> &first_object, OPERATIONS operation, const std::string &color, const std::string &style)
{
    int operation_id = print_oper(operation, color, style);

    print_edge(first_object.id_, operation_id);
    first_object.id_ = -1;
    print_node(first_object);
    print_edge(operation_id, first_object.id_);

    return operation_id;
}

int Tracker::print_oper(OPERATIONS operation, const std::string &color, const std::string &style)
{
    if (operation == OPERATIONS::EQ_COPY || operation == OPERATIONS::CONSTRUCTOR_COPY)
    {
        copy_count_ ++;
    }

    else if (operation == OPERATIONS::EQ_MOVE || operation == OPERATIONS::CONSTRUCTOR_MOVE)
    {

        move_count_ ++;
    }

    ++id;
    std::string string = std::to_string(id) + "[label=\"" + operations_[int(operation)] + "\"" + " color = \"" + color + "\" " + "style = " + "\"" + style + "\"];";
    file_ << string << std::endl;

    return id;
}

template<class T>
void Tracker::print_node(SuperType<T> &object)
{
    if (object.id_ == -1)
    {
        object.id_ = ++id;
    }
    
    std::string string = std::to_string(object.id_) + "[label=\"{ {name: " + object.name_ + "} | {value:" + std::to_string(object.value_) + "} | {address: " + std::to_string(uint64_t(&object)) + "}} \" " + 
                                                    + "color=" + "\"" + object.color_ + "\"" + "style=" + "\"" + object.style_ + "\"" + "];";
    file_ << string << std::endl;
}

void Tracker::print_edge(int id1, int id2) 
{
    file_ << std::to_string(id1) + "->" + std::to_string(id2) + ";" << std::endl;
}

void Tracker::print_open_func(const std::string &name)
{
    file_ << "subgraph " << "\"cluster_" << func_id << "\" {" << std::endl;
    file_ << "label = " << name << ";" << std::endl; 
    file_  << "style= filled" << std::endl;
    file_ << "color = " << "\"" << "#00000010" << "\";" << std::endl;

    func_id++;
}

void Tracker::print_close_func(const std::string &name)
{
    file_ << "}" << std::endl;
}

void Tracker::create_file(const std::string &file_name)
{   
    std::ofstream file;

    file_.open(file_name);
    file_ << "digraph G{\ntrankdir=HR;\nnode[shape=Mrecord];\n" << std::endl;
}

void Tracker::close_file()
{         
    file_ << "}";
    file_.close();
    system(("dot -T png " + file_name_ + ".dot > " + file_name_  + ".png").c_str());
}