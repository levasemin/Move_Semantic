#pragma once

#include "limits.hpp"
#include <iostream>
#include <string>
#include <fstream>

static int number_ = 0;
static int id = 0;

template<class T>
class SuperType
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

    class Tracker;

public:
    std::string name_;

    static Tracker tracker_;

    SuperType<T>(const T &value, const std::string &name = "");
    
    SuperType<T>(const SuperType<T> &that, const std::string &name = "");    
    SuperType<T> &operator= (const SuperType<T> &that);

    SuperType<T>(SuperType<T> &&that, const std::string &name = "");
    SuperType<T> &operator= (SuperType<T> &&that);

    ~SuperType<T>();

    SuperType<T> &operator+= (const SuperType<T> &that);
    SuperType<T> &operator-= (const SuperType<T> &that);
    SuperType<T> &operator*= (const SuperType<T> &that);
    SuperType<T> &operator/= (const SuperType<T> &that);
    SuperType<T> &operator^= (const SuperType<T> &that);
    SuperType<T> &operator&= (const SuperType<T> &that);
    SuperType<T> &operator|= (const SuperType<T> &that);
    SuperType<T> &operator%= (const SuperType<T> &that);

    SuperType<T> operator+ (const SuperType<T> &that);
    SuperType<T> operator- (const SuperType<T> &that);
    SuperType<T> operator* (const SuperType<T> &that);
    SuperType<T> operator/ (const SuperType<T> &that);
    SuperType<T> operator^ (const SuperType<T> &that);
    SuperType<T> operator& (const SuperType<T> &that);
    SuperType<T> operator| (const SuperType<T> &that);
    SuperType<T> operator% (const SuperType<T> &that);

    void *operator new   (size_t bytes, bool log_mode);
    void *operator new[] (size_t bytes, bool log_mode);
    void *operator new   (size_t bytes, void *place, bool log_mode);
    void *operator new[] (size_t bytes, void *place, bool log_mode);

    void operator delete   (void *pointer, size_t bytes);
    void operator delete[] (void *pointer, size_t bytes);

    const SuperType<T>& operator++(int);
    const SuperType<T>  operator++();
    const SuperType<T>& operator--(int);
    const SuperType<T>  operator--();

    operator T() const
    {
        return value_;
    }

    const SuperType<T> &operator[] (size_t index) const = delete;
    SuperType<T> &operator[] (size_t index) = delete;
};      

template<class T>
typename SuperType<T>::Tracker SuperType<T>::tracker_("graph.dot");

template<class T>
SuperType<T>::SuperType(const T &value, const std::string &name): 
    value_(value), 
    name_(name)
{
    if (!name.size())
    {
        name_ = "tmp" + std::to_string(number_);
        number_++;
    }

    std::cout << "Constructor " << name_ << std::endl; 
    tracker_.print_node(*this);
}

template<class T>
SuperType<T>::SuperType(const SuperType<T> &that, const std::string &name): 
    value_(that.value_), 
    name_(name)
{
    if (!name_.size())
    {
        name_ = "tmp" + std::to_string(number_);
        number_++;
    }

    std::cout << "Copy constructor " << name_ << std::endl; 

    tracker_.print_oper("copy", "red");
    int operation_id = id++;

    tracker_.print_edge(that.id_, operation_id);
    tracker_.print_node(*this);
    tracker_.print_edge(operation_id, id_);
}

template<class T>
SuperType<T> &SuperType<T>::operator= (const SuperType<T> &that)
{
    this->value_ = that.value_;

    std::cout << "Operator = " << name_ << std::endl; 
    
    tracker_.print_operation(*this, that, *this, "= (copy)", "red");

    return *this;
}


template<class T>
SuperType<T>::SuperType(SuperType<T> &&that, const std::string &name): 
    value_(that.value_), 
    name_(name)
{
    if (!name_.size())
    {
        name_ = "tmp" + std::to_string(number_);
        number_++;
    }

    std::cout << "Copy constructor " << name_ << std::endl; 

    tracker_.print_oper("move", "green");
    int operation_id = id++;

    tracker_.print_edge(that.id_, operation_id);
    tracker_.print_node(*this);
    tracker_.print_edge(operation_id, id_);
}

template<class T>
SuperType<T> &SuperType<T>::operator= (SuperType<T> &&that)
{
    if (this != &that)
    {
        this->value_ = that.value_;

        std::cout << "Operator = " << name_ << std::endl; 
    
        tracker_.print_operation(*this, that, *this, "= (move)", "green");
    }

    return *this;
}


template<class T>
SuperType<T>::~SuperType<T>()
{
    std::cout << "Destructor " << name_ << std::endl;
}    


template<class T>
SuperType<T> &SuperType<T>::operator+= (const SuperType<T> &that)
{
    if (ADD_LIMIT < current_add_)
    {
        std::cout << "Please buy license" << std::endl;

        return *this;
    }
    
    value_ += that.value_;
    current_add_++;

    std::cout << "Operator " << name_ << " += " <<  that.name_ << std::endl;
    tracker_.print_operation(*this, that, *this, "+=");

    return *this;
}

template<class T>
SuperType<T> &SuperType<T>::operator-= (const SuperType<T> &that)
{
    if (SUB_LIMIT < current_sub_)
    {
        std::cout << "Please buy license" << std::endl;

        return *this;
    }
    
    value_ -= that.value_;
    current_sub_++;

    std::cout << "Operator " << name_ << " -= " <<  that.name_ << std::endl;
    tracker_.print_operation(*this, that, *this, "-=");

    return *this;
}

template<class T>
SuperType<T> &SuperType<T>::operator*= (const SuperType<T> &that)
{
    if (MUL_LIMIT < current_mul_)
    {
        std::cout << "Please buy license" << std::endl;

        return *this;
    }

    
    value_ *= that.value_;
    current_mul_++;

    std::cout << "Operator " << name_ << " *= " <<  that.name_ << std::endl;
    tracker_.print_operation(*this, that, *this, "*=");
    
    return *this;
}

template<class T>
SuperType<T> &SuperType<T>::operator/= (const SuperType<T> &that)
{
    if (DIV_LIMIT < current_div_)
    {
        std::cout << "Please buy license" << std::endl;

        return *this;
    }
    
    value_ /= that.value_;
    current_div_++;

    std::cout << "Operator " << name_ << " /= " <<  that.name_ << std::endl;
    tracker_.print_operation(*this, that, *this, "/=");
    
    return *this;
}

template<class T>
SuperType<T> &SuperType<T>::operator^= (const SuperType<T> &that)
{
    if (DEGREE_LIMIT < current_degree_)
    {
        std::cout << "Please buy license" << std::endl;

        return *this;
    }
    
    value_ ^= that.value_;
    current_degree_++;

    std::cout << "Operator " << name_ << " ^= " <<  that.name_ << std::endl;
    tracker_.print_operation(*this, that, *this, "^=");

    return *this;
}

template<class T>
SuperType<T> &SuperType<T>::operator&= (const SuperType<T> &that)
{
    if (BIT_AND_LIMIT < current_bit_and_)
    {
        std::cout << "Please buy license" << std::endl;

        return *this;
    }
    
    value_ &= that.value_;
    current_bit_and_++;

    std::cout << "Operator " << name_ << " &= " <<  that.name_ << std::endl;
    tracker_.print_operation(*this, that, *this, "&=");

    return *this;
}

template<class T>
SuperType<T> &SuperType<T>::operator|= (const SuperType<T> &that)
{
    if (BIT_OR_LIMIT < current_bit_or_)
    {
        std::cout << "Please buy license" << std::endl;

        return *this;
    }
    
    value_ |= that.value_;
    current_bit_or_++;

    std::cout << "Operator " << name_ << " |= " <<  that.name_ << std::endl;
    tracker_.print_operation(*this, that, *this, "|=");

    return *this;
}

template<class T>
SuperType<T> &SuperType<T>::operator%= (const SuperType<T> &that)
{
    if (MOD_LIMIT < current_mod_)
    {
        std::cout << "Please buy license" << std::endl;

        return *this;
    }
    
    value_ %= that.value_;
    current_mod_++;

    std::cout << "Operator " << name_ << " %= " <<  that.name_ << std::endl;
    tracker_.print_operation(*this, that, *this, "%=");

    return *this;
}

template<class T>
SuperType<T> SuperType<T>::operator+ (const SuperType<T> &that)
{

    SuperType<T> new_that(*this);

    new_that += that;

    return new_that;
}

template<class T>
SuperType<T> SuperType<T>::operator- (const SuperType<T> &that)
{
    if (SUB_LIMIT > current_sub_)
    {
        std::cout << "Operator " << name_ << " - " <<  that.name_ << std::endl;
    }

    SuperType<T> new_that = *this;
    new_that -= that;

    return new_that;
}

template<class T>
SuperType<T> SuperType<T>::operator* (const SuperType<T> &that)
{
    SuperType<T> new_that = *this;
    new_that *= that;

    return new_that;
}

template<class T>
SuperType<T> SuperType<T>::operator/ (const SuperType<T> &that)
{
    SuperType<T> new_that = *this;
    new_that /= that;

    return new_that;
}

template<class T>
SuperType<T> SuperType<T>::operator^ (const SuperType<T> &that)
{
    SuperType<T> new_that = *this;
    new_that ^= that;

    return new_that;
}

template<class T>
SuperType<T> SuperType<T>::operator& (const SuperType<T> &that)
{
    SuperType<T> new_that = *this;
    new_that &= that;

    return new_that;
}

template<class T>
SuperType<T> SuperType<T>::operator| (const SuperType<T> &that)
{
    SuperType<T> new_that = *this;
    new_that |= that;

    return new_that;
}

template<class T>
SuperType<T> SuperType<T>::operator% (const SuperType<T> &that)
{
    SuperType<T> new_that = *this;
    new_that %= that;
    
    return new_that;
}

template<class T>
void *SuperType<T>::operator new (size_t bytes, bool log_mode)
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

template<class T>
void *SuperType<T>::operator new[] (size_t bytes, bool log_mode)
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

template<class T>
void *SuperType<T>::operator new (size_t bytes, void *place, bool log_mode)
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

template<class T>
void *SuperType<T>::operator new[] (size_t bytes, void *place, bool log_mode)
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

template<class T>
void SuperType<T>::operator delete (void *pointer, size_t bytes)
{
    bool log_mode = true;

    if (log_mode)
    {
        std::cout << "Deallocated " << bytes << " bytes by delete" << std::endl;
    }

    free(pointer);   
}

template<class T>
void SuperType<T>::operator delete[] (void *pointer, size_t bytes)
{
    bool log_mode = true;

    if (log_mode)
    {
        std::cout << "Deallocated " << bytes << " bytes by delete[]" << std::endl;
    }

    free(pointer);
}


template<class T>
const SuperType<T>& SuperType<T>::operator++(int) 
{
    value_++;

    tracker_.print_operation(*this, "++");
    
    return *this;
}

template<class T>
const SuperType<T> SuperType<T>::operator++() 
{
    SuperType<T> oldValue(*this);
    value_++;

    tracker_.print_operation(*this, "++");

    return oldValue;
}

template<class T>
const SuperType<T> SuperType<T>::operator--() 
{
    SuperType<T> oldValue(*this);
    value_--;

    tracker_.print_operation(*this, "--");
    
    return oldValue;
}

template<class T>
const SuperType<T>& SuperType<T>::operator--(int) 
{
    value_--;
    
    tracker_.print_operation(*this, "--");
    
    return *this;
}