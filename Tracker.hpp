#pragma once
#include "SuperType.hpp"

template<class T>
class SuperType<T>::Tracker
    {
        std::ofstream file_;

    public:
        Tracker(const std::string &file_name = "graph.dot")
        {
            file_.open(file_name);
            file_ << "digraph G{\nrankdir=LR;\nnode[shape=Mrecord];\n" << std::endl;
        }

        void print_operation(const SuperType<T> &first_object, const SuperType<T> &second_object, SuperType<T> &result, std::string operation, const std::string &color = "black")
        {
            tracker_.print_oper(operation, color);
            int operation_id = id;

            tracker_.print_edge(first_object.id_, operation_id);
            tracker_.print_edge(second_object.id_, operation_id);
            tracker_.print_node(result);
            tracker_.print_edge(operation_id, result.id_);
        }

        void print_operation(SuperType<T> &first_object, std::string operation, const std::string &color = "black")
        {
            tracker_.print_oper(operation, color);
            int operation_id = id;

            tracker_.print_edge(first_object.id_, operation_id);
            tracker_.print_node(first_object);
            tracker_.print_edge(operation_id, first_object.id_);
        }

        void print_oper(const std::string &operation, const std::string &color = "black")
        {
            ++id;
            std::string string = std::to_string(id) + "[label=\"" + operation + "\"" + " color = \"" + color + "\"];";
            file_ << string << std::endl;
        }

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
        
        ~Tracker()
        {
            file_ << "}";
            file_.close();
        }
    };