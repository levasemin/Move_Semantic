#pragma once
#include <iostream>
#include <fstream>
#include <stack>

template <class T>
class SuperType;


class Tracker
{
public:
    static Tracker &getInstance()
    {
        static Tracker tracker;
        return tracker;
    }

    template <class T>
    void print_operation(const SuperType<T> &first_object, const SuperType<T> &second_object, SuperType<T> &result, std::string operation, const std::string &color = "black")
    {
        print_oper(operation, color);
        int operation_id = id;

        print_edge(first_object.id_, operation_id);
        print_edge(second_object.id_, operation_id);
        print_node(result);
        print_edge(operation_id, result.id_);
    }

    template<class T>
    int print_operation(SuperType<T> &first_object, std::string operation, const std::string &color = "black")
    {
        int operation_id = print_oper(operation, color);;

        print_edge(first_object.id_, operation_id);
        print_node(first_object);
        print_edge(operation_id, first_object.id_);

        return operation_id;
    }

    int print_oper(const std::string &operation, const std::string &color = "black", const std::string &style = "")
    {
        ++id;
        std::string string = std::to_string(id) + "[label=\"" + operation + "\"" + " color = \"" + color + "\" " + "style = " + "\"" + style + "\"];";
        file_ << string << std::endl;

        return id;
    }

    template<class T>
    void print_node(SuperType<T> &object)
    {
        object.id_ = ++id;
        std::string string = std::to_string(object.id_) + "[label=\" name: " + object.name_ + " | value:" + std::to_string(object.value_) + " | address: " + std::to_string(uint64_t(&object)) + " \" ];";
        file_ << string << std::endl;
    }

    void print_edge(int id1, int id2) 
    {
        file_ << std::to_string(id1) + "->" + std::to_string(id2) + ";" << std::endl;
    }
    
    void print_open_func(const std::string &name)
    {
        file_ << "subgraph " << "\"cluster_" << func_id << "\" {" << std::endl;
        file_ << "label = " << name << ";" << std::endl; 
        file_ << "color = " << "\"" << std::to_string(int(func_color_)) << "." << std::to_string(int(func_color_ * 100) % 100) << ",1,1\"" << ";" << std::endl;

        func_id++;
        func_color_ = func_color_ + 0.15 > 1 ? 0 : func_color_ + 0.15;
    }

    void print_close_func(const std::string &name)
    {
        file_ << "}" << std::endl;
    }

    void create_file(const std::string &file_name)
    {   
        std::ofstream file;

        file_.open(file_name);
        file_ << "digraph G{\nrankdir=LR;\nnode[shape=Mrecord];\n" << std::endl;
    }

    void close_file()
    {         
        file_ << "}";
        file_.close();
        std::cout << "dot -T png " + file_name_ + ".dot > " + file_name_  + ".png";
        system(("dot -T png " + file_name_ + ".dot > " + file_name_  + ".png").c_str());
    }

private:

    std::ofstream file_;
    std::string file_name_;

    int func_id = 0;
    int id = 0;

    float func_color_ = 0;
    Tracker(const std::string &file_name = "graph.dot") : 
        file_name_(file_name),
        file_()
    {
        file_name_.erase(file_name_.end()-4, file_name_.end());
        create_file(file_name);
    }

    ~Tracker()
    {
        close_file();
    }

    Tracker(const Tracker&);
    Tracker& operator=(const Tracker&);
};