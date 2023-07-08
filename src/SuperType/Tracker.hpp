#pragma once

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

#define start_function() SL::Tracker::getInstance().print_open_func(__func__);
#define end_function()   SL::Tracker::getInstance().print_close_func();

namespace SL
{
    
template <class T>
class SuperType;

struct style_params
{
    std::string color_ = "";
    std::string style_ = "";
    std::string label_ = "";
    std::string font_color_ = "";
};

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
    
    template<class T>
    void print_destructor(SuperType<T> &object, const style_params &style);

    void print_open_func(const std::string &name);

    void print_close_func();

    void open_file(const std::string &file_name);

    void close_file();

private:

    std::string file_name_ = "";
    std::ofstream file_;

    int func_id = 0;
    int id = 0;

    int copy_count_ = 0;
    int move_count_ = 0;
    
    Tracker() : file_()
    {
    }

    ~Tracker()
    {
        if (file_name_.size())
        {
            file_ << "label=\"Count of copy operation: " << copy_count_ << "\n" << "Count of move operation: " << move_count_ << "\"";
        }
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

    if (style.label_ != operations_[CONSTRUCTOR_COPY] && style.label_ != operations_[CONSTRUCTOR_MOVE])
    {
        print_edge(first_object.id_, operation_id, style_edge);
    }

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
    
    if (file_name_.size())
    {
        file_   << std::to_string(id)
                << "[" 
                    << "label = \""     << style.label_      << "\" " 
                    << "color = \""     << style.color_      << "\" " 
                    << "style = \""     << style.style_      << "\" " 
                    << "fontcolor = \"" << style.font_color_ << "\" "
                << "];" << std::endl;
    }

    return id;
}

template<class T>
void Tracker::print_destructor(SuperType<T> &object, const style_params &style)
{
    print_oper(style);
    style_params style_edge = {"", "", std::to_string(step_number_++)};
    print_edge(object.id_, id, style_edge);
}

template<class T>
void Tracker::print_node(SuperType<T> &object)
{
    if (object.id_ == -1)
    {
        object.id_ = ++id;
    }
    
    if (file_name_.size())
    {
        file_   << object.id_ 
                << "["
                    <<"label=\"{ " 
                        << "{name: " << object.style_.label_ << "} | "
                        << "{value:" << object.value_ << "} | "
                        << "{address: " << uint64_t(&object) << "}"
                    <<"} \" " 
                    << "color=" << "\"" << object.style_.color_ << "\"" 
                    << "style=" << "\"" << object.style_.style_ << "\"" 
                    << "fontcolor=" << "\"" << object.style_.font_color_ << "\"" 
                << "];" << std::endl;
    }
}

void Tracker::print_edge(int id1, int id2, const style_params &style) 
{
    if (file_name_.size())
    {
        file_ << "edge["
              << "style = \""  << style.style_ << "\" " 
              << "color = \""  << style.color_ << "\"" 
              << "label = \""  << style.label_ << "\"" 
              << "fontcolor = \"" << style.font_color_ <<"\"]" 
              << std::to_string(id1) << "->" << std::to_string(id2) << ";" << std::endl;
    }
}

void Tracker::print_open_func(const std::string &name)
{
    if (file_name_.size())
    {
        file_ << "subgraph " << "\"cluster_" << func_id << "\" {" << std::endl
              << "label = " << name << ";" << std::endl
              << "style = filled" << std::endl
              << "color = " << "\"" << "#00000010" << "\";" << std::endl;
    }

    func_id++;
}

std::string Tracker::get_operation_name(int operation)
{
    return operations_[operation];
}

void Tracker::print_close_func()
{
    if (file_name_.size())
    {
        file_ << "}" << std::endl;
    }
}

void Tracker::open_file(const std::string &file_name)
{   
    if (file_name_ != "")
    {
        close_file();
    }

    file_name_ = file_name;
    
    system("mkdir ../dot");
    file_.open("../dot/" + file_name + ".dot");

    if (file_name.size())
    {
        if (file_name_.size())
        {
            file_ << "digraph G{\ntrankdir=HR;\nnode[shape=Mrecord];\n" << std::endl;
        }
    }
}

void Tracker::close_file()
{         
    if (file_name_.size())
    {
        file_ << "}";
        file_.close();

        system(("dot -T png ../dot/" + file_name_ + ".dot > " + "../" + file_name_  + ".png").c_str());
    }
}

};