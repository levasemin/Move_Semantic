#pragma once
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
template <class T>


class SuperType;

enum operations_
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
    INC,
    DEC,
    EQ_COPY,
    EQ_MOVE,
    CONSTRUCTOR_COPY,
    CONSTRUCTOR_MOVE
};

struct style_params
{
    std::string color_ = "";
    std::string style_ = "";
    std::string label_ = "";
};

class Tracker
{
public:
    static Tracker &getInstance()
    {
        static Tracker tracker;
        return tracker;
    }

    int step_number_ = 1;
    std::vector<std::string> operations_ = {"+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "+", "-", "*", "/", "%", "&", "|", "^", "++", "--", "= (copy)", "= (move)", "copy", "move"};
    
    std::string get_operation_name(int operation);

    template <class T>
    void print_operation(const SuperType<T> &first_object, const SuperType<T> &second_object, SuperType<T> &result, const style_params &style = {});

    template<class T>
    int print_operation(SuperType<T> &first_object, const style_params &style = {});

    int print_oper(const style_params &style = {});

    template<class T>
    void print_node(SuperType<T> &object);

    void print_edge(int id1, int id2, const style_params &style = {});
    
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
void Tracker::print_operation(const SuperType<T> &first_object, const SuperType<T> &second_object, SuperType<T> &result, const style_params &style)
{
    print_oper(style);
    int operation_id = id;

    style_params style_edge = {"", "", std::to_string(step_number_)};

    print_edge(first_object.id_, operation_id, style_edge);

    if (style.label_ == operations_[EQ_COPY] || style.label_ == operations_[EQ_MOVE])
    {
        style_edge.style_ = "dashed";
    }

    print_edge(second_object.id_, operation_id, style_edge);
    result.id_ = -1;
    print_node(result);
    
    print_edge(operation_id, result.id_, {"", "", std::to_string(step_number_++)});
}

template<class T>
int Tracker::print_operation(SuperType<T> &first_object, const style_params &style)
{
    int operation_id = print_oper(style);
    
    style_params style_edge = {"", "", std::to_string(step_number_++)};
    print_edge(first_object.id_, operation_id);
    first_object.id_ = -1;
    print_node(first_object);
    style_edge.label_ = std::to_string(step_number_++);
    print_edge(operation_id, first_object.id_, style_edge);

    return operation_id;
}

int Tracker::print_oper(const style_params &style)
{
    if (style.label_ == operations_[operations_::EQ_COPY] || style.label_ == operations_[operations_::CONSTRUCTOR_COPY])
    {
        copy_count_ ++;
    }

    else if (style.label_ == operations_[operations_::EQ_MOVE] || style.label_ == operations_[operations_::CONSTRUCTOR_MOVE])
    {

        move_count_ ++;
    }

    ++id;
    std::string string = std::to_string(id) + "[label=\"" + style.label_ + "\"" + " color = \"" + style.color_ + "\" " + "style = " + "\"" + style.style_ + "\"];";
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
    
    std::string string = std::to_string(object.id_) + "[label=\"{ {name: " + object.style_.label_ + "} | {value:" + std::to_string(object.value_) + "} | {address: " + std::to_string(uint64_t(&object)) + "}} \" " + 
                                                    + "color=" + "\"" + object.style_.color_ + "\"" + "style=" + "\"" + object.style_.style_ + "\"" + "];";
    file_ << string << std::endl;
}

void Tracker::print_edge(int id1, int id2, const style_params &style) 
{
    file_ << "edge[style = \"" << style.style_ << "\" " << "color = \"" << style.color_  << "\"" << "label = \"" + style.label_ + "\"" << "]" << std::to_string(id1) + "->" + std::to_string(id2) + ";" << std::endl;
}

void Tracker::print_open_func(const std::string &name)
{
    file_ << "subgraph " << "\"cluster_" << func_id << "\" {" << std::endl;
    file_ << "label = " << name << ";" << std::endl; 
    file_ << "style= filled" << std::endl;
    file_ << "color = " << "\"" << "#00000010" << "\";" << std::endl;

    func_id++;
}

std::string Tracker::get_operation_name(int operation)
{
    return operations_[operation];
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