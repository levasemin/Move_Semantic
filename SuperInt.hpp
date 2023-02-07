#pragma once

#include "limits.hpp"
#include "graphiz.hpp"
#include <iostream>
#include <string>

static int number_ = 0;
static int id = 0;

template<class T>
class SuperInt
{
    T value_;
    int id_ = 0; 
    int current_add_ = 0; 
    int current_sub_ = 0;
    int current_mul_ = 0;
    int current_div_ = 0;
    int current_degree_ = 0;
    int current_bit_and_ = 0;
    int current_bit_or_ = 0;
    int current_mod_ = 0;

    bool log_;

    class Tracker
    {
        std::ofstream file_;

    public:
        Tracker(const std::string &file_name = "graph.dot")
        {
            file_.open(file_name);
            file_ << "digraph G{\nrankdir=LR;\nnode[shape=Mrecord];\n" << std::endl;
        }

        void print_operation(const SuperInt<T> &first_object, const SuperInt<T> &second_object, SuperInt<T> &result, std::string operation)
        {
            tracker_.print_oper(operation);
            int operation_id = id;

            tracker_.print_edge(first_object.id_, operation_id);
            tracker_.print_edge(second_object.id_, operation_id);
            tracker_.print_node(result);
            tracker_.print_edge(operation_id, result.id_);
        }

        void print_operation(const SuperInt<T> &first_object, std::string operation)
        {
            tracker_.print_oper(operation);
            int operation_id = id;

            tracker_.print_edge(first_object.id_, operation_id);
            tracker_.print_node(first_object);
            tracker_.print_edge(operation_id, first_object.id_);
        }

        void print_oper(const std::string &operation)
        {
            ++id;
            std::string string = std::to_string(id) + "[label=\"" + operation + " \" ];";
            file_ << string << std::endl;
        }

        void print_node(SuperInt<T> &object)
        {
            object.id_ = ++id;
            std::string string = std::to_string(object.id_) + "[label=\"" + object.name_ + " | " + std::to_string(object.value_) + " \" ];";
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

public:
    std::string name_;

    static Tracker tracker_;

    SuperInt<T>(const T &value, const std::string &name = ""): 
        value_(value), 
        name_(name)
    {
        if (!name.size())
        {
            name_ = "temp" + std::to_string(number_);
            number_++;
        }

        std::cout << "Constructor " << name_ << std::endl; 
        tracker_.print_node(*this);
    }

    SuperInt<T>(const SuperInt<T> &that, const std::string &name = ""): 
        value_(that.value_), 
        name_(name)
    {
        if (!name_.size())
        {
            name_ = "temp" + std::to_string(number_);
            number_++;
        }

        std::cout << "Copy constructor " << name_ << std::endl; 

        tracker_.print_oper("copy");
        int operation_id = id++;

        tracker_.print_edge(that.id_, operation_id);
        tracker_.print_node(*this);
        tracker_.print_edge(operation_id, id_);
    }
    
    SuperInt<T> operator= (const SuperInt<T> &that)
    {
        this->value_ = that.value_;

        std::cout << "Operator = " << name_ << std::endl; 
        
        tracker_.print_operation(*this, that, *this, "=");

        return *this;
    }

    ~SuperInt<T> ()
    {
        std::cout << "Destructor " << name_ << std::endl;
    }

    SuperInt<T> &operator+= (const SuperInt<T> &that)
    {
        if (ADD_LIMIT < current_add_)
        {
            std::cout << "Please buy license" << std::endl;

            return *this;
        }
        
        value_ += that.value_;
        current_add_++;

        if (log_ == true)
        {
            std::cout << "Operator " << name_ << " += " <<  that.name_ << std::endl;
            
            tracker_.print_operation(*this, that, *this, "+=");
        }

        return *this;
    }

    SuperInt<T> &operator-= (const SuperInt<T> &that)
    {
        if (SUB_LIMIT < current_sub_)
        {
            std::cout << "Please buy license" << std::endl;

            return *this;
        }

        std::cout << "Operator " << name_ << " -= " <<  that.name_ << std::endl;
        
        value_ -= that.value_;
        current_sub_++;

        if (log_)
        {
            tracker_.print_operation(*this, that, *this, "-=");
        }

        return *this;
    }

    SuperInt<T> &operator*= (const SuperInt<T> &that)
    {
        if (MUL_LIMIT < current_mul_)
        {
            std::cout << "Please buy license" << std::endl;

            return *this;
        }

        std::cout << "Operator " << name_ << " *= " <<  that.name_ << std::endl;
        
        value_ *= that.value_;
        current_mul_++;

        if (log_)
        {
            tracker_.print_operation(*this, that, *this, "*=");
        }

        return *this;
    }

    SuperInt<T> &operator/= (const SuperInt<T> &that)
    {
        if (DIV_LIMIT < current_div_)
        {
            std::cout << "Please buy license" << std::endl;

            return *this;
        }

        std::cout << "Operator " << name_ << " /= " <<  that.name_ << std::endl;
        
        value_ /= that.value_;
        current_div_++;

        if (log_)
        {
            tracker_.print_operation(*this, that, *this, "/=");
        }
        return *this;
    }

    SuperInt<T> &operator^= (const SuperInt<T> &that)
    {
        if (DEGREE_LIMIT < current_degree_)
        {
            std::cout << "Please buy license" << std::endl;

            return *this;
        }

        std::cout << "Operator " << name_ << " ^= " <<  that.name_ << std::endl;
        
        value_ ^= that.value_;
        current_degree_++;

        if (log_)
        {
            tracker_.print_operation(*this, that, *this, "^=");
        }

        return *this;
    }

    SuperInt<T> &operator&= (const SuperInt<T> &that)
    {
        if (BIT_AND_LIMIT < current_bit_and_)
        {
            std::cout << "Please buy license" << std::endl;

            return *this;
        }

        std::cout << "Operator " << name_ << " &= " <<  that.name_ << std::endl;
        
        value_ &= that.value_;
        current_bit_and_++;

        if (log_)
        {
            tracker_.print_operation(*this, that, *this, "&=");
        }

        return *this;
    }
    
    SuperInt<T> &operator|= (const SuperInt<T> &that)
    {
        if (BIT_OR_LIMIT < current_bit_or_)
        {
            std::cout << "Please buy license" << std::endl;

            return *this;
        }

        std::cout << "Operator " << name_ << " |= " <<  that.name_ << std::endl;
        
        value_ |= that.value_;
        current_bit_or_++;

        if (log_)
        {
            tracker_.print_operation(*this, that, *this, "|=");
        }

        return *this;
    }

    SuperInt<T> &operator%= (const SuperInt<T> &that)
    {
        if (MOD_LIMIT < current_mod_)
        {
            std::cout << "Please buy license" << std::endl;

            return *this;
        }

        std::cout << "Operator " << name_ << " %= " <<  that.name_ << std::endl;
        
        value_ %= that.value_;
        current_mod_++;

        if (log_)
        {
            tracker_.print_operation(*this, that, *this, "%=");
        }

        return *this;
    }

    SuperInt<T> operator+ (const SuperInt<T> &that)
    {
        log_ = false;

        if (ADD_LIMIT > current_add_)
        {
            std::cout << "Operator " << name_ << " + " <<  that.name_ << std::endl;
        }

        SuperInt<T> new_that(*this);

        log_ = false;

        new_that += that;

        tracker_.print_operation(*this, that, new_that, "+");

        log_ = true;

        return new_that;
    }

    SuperInt<T> operator- (const SuperInt<T> &that)
    {
        log_ = false;

        if (SUB_LIMIT > current_sub_)
        {
            std::cout << "Operator " << name_ << " - " <<  that.name_ << std::endl;
        }

        std::cout << "Operator - " << std::endl;

        SuperInt<T> new_that = *this;
        new_that -= that;

        tracker_.print_operation(*this, that, new_that, "-");

        log_ = true;

        return new_that;
    }

    SuperInt<T> operator* (const SuperInt<T> &that)
    {
        log_ = false;

        if (MUL_LIMIT > current_mul_)
        {
            std::cout << "Operator " << name_ << " * " <<  that.name_ << std::endl;
        }

        SuperInt<T> new_that = *this;
        new_that *= that;

        tracker_.print_operation(*this, that, new_that, "*");

        log_ = true;

        return new_that;
    }

    SuperInt<T> operator/ (const SuperInt<T> &that)
    {
        log_ = false;

        if (DIV_LIMIT > current_div_)
        {
            std::cout << "Operator " << name_ << " / " <<  that.name_ << std::endl;
        }

        SuperInt<T> new_that = *this;
        new_that /= that;

        tracker_.print_operation(*this, that, new_that, "/");

        log_ = true;

        return new_that;
    }

    SuperInt<T> operator^ (const SuperInt<T> &that)
    {
        log_ = false;

        if (DEGREE_LIMIT > current_degree_)
        {
            std::cout << "Operator " << name_ << " ^ " <<  that.name_ << std::endl;
        }

        SuperInt<T> new_that = *this;
        new_that ^= that;

        tracker_.print_operation(*this, that, new_that, "^");

        log_ = true;

        return new_that;
    }

    SuperInt<T> operator& (const SuperInt<T> &that)
    {
        log_ = false;

        if (BIT_AND_LIMIT > current_bit_and_)
        {
            std::cout << "Operator " << name_ << " & " <<  that.name_ << std::endl;
        }

        SuperInt<T> new_that = *this;
        new_that &= that;

        tracker_.print_operation(*this, that, new_that, "&");

        log_ = true;

        return new_that;
    }

    SuperInt<T> operator| (const SuperInt<T> &that)
    {
        log_ = false;

        if (DEGREE_LIMIT > current_degree_)
        {
            std::cout << "Operator " << name_ << " | " <<  that.name_ << std::endl;
        }

        SuperInt<T> new_that = *this;
        new_that |= that;

        tracker_.print_operation(*this, that, new_that, "|");

        log_ = true;

        return new_that;
    }

    SuperInt<T> operator% (const SuperInt<T> &that)
    {
        log_ = false;

        if (DEGREE_LIMIT > current_mod_)
        {
            std::cout << "Operator " << name_ << " % " <<  that.name_ << std::endl;
        }

        SuperInt<T> new_that = *this;
        new_that %= that;

        tracker_.print_operation(*this, that, new_that, "%");

        log_ = true;

        return new_that;
    }

    void *operator new (size_t bytes, bool log_mode)
    {
        if (log_mode)
        {
            std::cout << "Allocated " << bytes << " bytes by new" << std::endl;
        }

        void *place = calloc(1, bytes);

        if (place == nullptr)
        {
            std::bad_alloc exception;
            throw exception;
        }

        return place;
    }

    void *operator new[] (size_t bytes, bool log_mode)
    {
        if (log_mode)
        {
            std::cout << "Allocated " << bytes << " bytes by new[]" << std::endl;
        }
        
        void *place = calloc(1, bytes);

        if (place == nullptr)
        {
            std::bad_alloc exception;
            throw exception;
        }    

        return place;
    }

    void *operator new (size_t bytes, void *place, bool log_mode)
    {
        if (log_mode)
        {
            std::cout << "Replacemented " << bytes << " bytes by new" << std::endl;
        }

        if (place == nullptr)
        {
            std::bad_alloc exception;
            throw exception;
        }    

        return place;
    }

    void *operator new[] (size_t bytes, void *place, bool log_mode)
    {
        if (log_mode)
        {
            std::cout << "Replacemented " << bytes << " bytes by new[]" << std::endl;
        }

        if (place == nullptr)
        {
            std::bad_alloc exception;
            throw exception;
        }    
        
        return place;
    }

    void operator delete (void *pointer, size_t bytes)
    {
        bool log_mode = true;

        if (log_mode)
        {
            std::cout << "Deallocated " << bytes << " bytes by delete" << std::endl;
        }

        free(pointer);   
    }

    void operator delete[] (void *pointer, size_t bytes)
    {
        bool log_mode = true;

        if (log_mode)
        {
            std::cout << "Deallocated " << bytes << " bytes by delete[]" << std::endl;
        }

        free(pointer);
    }

    const SuperInt<T>& operator++(int) 
    {
        value_++;

        tracker_.print_operation(*this, "++");
        
        return *this;
    }

    const SuperInt<T> operator++() 
    {
        SuperInt<T> oldValue(*this);
        value_++;

        tracker_.print_operation(*this, "++");

        return oldValue;
    }

    const SuperInt<T>& operator--(int) 
    {
        value_--;
        
        tracker_.print_operation(*this, "--");
        
        return *this;
    }

    const SuperInt<T> operator--() 
    {
        SuperInt<T> oldValue(*this);
        value_--;

        tracker_.print_operation(*this, "--");
        
        return oldValue;
    }

    operator T() const
    {
        return value_;
    }

    const SuperInt<T> &operator[] (size_t index) const = delete;
    SuperInt<T> &operator[] (size_t index) = delete;
};      

template<class T>
typename SuperInt<T>::Tracker SuperInt<T>::tracker_("graph.dot");