#pragma once

#include "limits.hpp"
#include "Tracker.hpp"
#include <iostream>
#include <string>

static int number_ = 0;

#define binary_operator(oper, type)                                                             \
SuperType<T> operator oper (const SuperType<T> &that)                                           \
{                                                                                               \
    log_ = false;                                                                               \
                                                                                                \
    if (type##_LIMIT > current_##type##_)                                                       \
    {                                                                                           \
        std::cout << "Operator " << name_ << " " << #oper << " " <<  that.name_ << std::endl;   \
    }                                                                                           \
                                                                                                \
    SuperType<T> new_that(*this);                                                               \
    new_that oper##= that;                                                                      \
                                                                                                \
    log_ = true;                                                                                \
                                                                                                \
    Tracker &tracker = Tracker::getInstance();                                                  \
                                                                                                \
    tracker.print_operation(*this, that, new_that, #oper);                                      \
                                                                                                \
    return new_that;                                                                            \
}                                                                               

#define mono_operator(oper, type)                                                               \
SuperType<T> &operator oper (const SuperType<T> &that)                                          \
{                                                                                               \
    if (type##_LIMIT < current_##type##_)                                                       \
    {                                                                                           \
        std::cout << "Please buy license" << std::endl;                                         \
                                                                                                \
        return *this;                                                                           \
    }                                                                                           \
                                                                                                \
    value_ oper that.value_;                                                                    \
    current_##type##_++;                                                                        \
                                                                                                \
    if (log_ == true)                                                                           \
    {                                                                                           \
        Tracker &tracker = Tracker::getInstance();                                              \
        std::cout << "Operator " << name_ << " " << #oper << " "<<  that.name_ << std::endl;    \
        tracker.print_operation(*this, that, *this, #oper);                                     \
    }                                                                                           \
                                                                                                \
    return *this;                                                                               \
}

template<class T>
class SuperType
{
    T value_;
    int id_ = 0; 
    int current_ADD_ = 0; 
    int current_SUB_ = 0;
    int current_MUL_ = 0;
    int current_DIV_ = 0;
    int current_DEGREE_ = 0;
    int current_BIT_AND_ = 0;
    int current_BIT_OR_ = 0;
    int current_MOD_ = 0;

    static bool log_;

public:
    std::string name_;

    SuperType<T>(const T &value, const std::string &name = "");
    
    SuperType<T>(const SuperType<T> &that, const std::string &name = "");    
    SuperType<T> &operator= (const SuperType<T> &that);

    // SuperType<T>(SuperType<T> &&that, const std::string &name = "");
    // SuperType<T> &operator= (SuperType<T> &&that);

    ~SuperType<T>();

    mono_operator(+=, ADD)
    mono_operator(-=, SUB)
    mono_operator(/=, DIV)
    mono_operator(*=, MUL)
    mono_operator(%=, MOD)
    mono_operator(&=, BIT_AND)
    mono_operator(|=, BIT_OR)
    mono_operator(^=, DEGREE)

    binary_operator(+, ADD)
    binary_operator(-, SUB)
    binary_operator(/, DIV)
    binary_operator(*, MUL)
    binary_operator(%, MOD)
    binary_operator(&, BIT_AND)
    binary_operator(|, BIT_OR)
    binary_operator(^, DEGREE)

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

    friend Tracker;
};      

template<class T>
bool SuperType<T>::log_(true);

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

    if (log_)
    {
        std::cout << "Constructor " << name_ << std::endl;

        Tracker &tracker = Tracker::getInstance();
        tracker.print_node(*this);
    }
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

    if (log_)
    {
        std::cout << "Copy constructor " << name_ << std::endl; 
        
        Tracker &tracker = Tracker::getInstance();
        
        int operation_id = tracker.print_oper("copy", "red", "filled");

        tracker.print_edge(that.id_, operation_id);
        tracker.print_node(*this);
        tracker.print_edge(operation_id, id_);
    }
}

template<class T>
SuperType<T> &SuperType<T>::operator= (const SuperType<T> &that)
{
    this->value_ = that.value_;

    if (log_)
    {
        Tracker &tracker = Tracker::getInstance();

        std::cout << "Operator = " << name_ << std::endl; 
        tracker.print_operation(*this, that, *this, "= (copy)", "red", "filled");
    }

    return *this;
}


// template<class T>
// SuperType<T>::SuperType(SuperType<T> &&that, const std::string &name): 
//     value_(that.value_), 
//     name_(name)
// {
//     if (!name_.size())
//     {
//         name_ = "tmp" + std::to_string(number_);
//         number_++;
//     }

//     if (log_)
//     {
//         std::cout << "Copy constructor " << name_ << std::endl; 

//         Tracker &tracker = Tracker::getInstance();

//         int operation_id = tracker.print_oper("move", "green", "filled");;

//         tracker.print_edge(that.id_, operation_id);
//         tracker.print_node(*this);
//         tracker.print_edge(operation_id, id_);
//     }
// }

// template<class T>
// SuperType<T> &SuperType<T>::operator= (SuperType<T> &&that)
// {
//     if (this != &that)
//     {
//         this->value_ = that.value_;
        
//         if (log_)
//         {
//             std::cout << "Operator = " << name_ << std::endl; 

//             Tracker &tracker = Tracker::getInstance();

//             tracker.print_operation(*this, that, *this, "= (move)", "green", "filled");
//         }
//     }

//     return *this;
// }


template<class T>
SuperType<T>::~SuperType<T>()
{
    std::cout << "Destructor " << name_ << std::endl;
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

    Tracker &tracker = Tracker::getInstance();

    tracker.print_operation(*this, "++");
    
    return *this;
}

template<class T>
const SuperType<T> SuperType<T>::operator++() 
{
    SuperType<T> oldValue(*this);
    value_++;

    Tracker &tracker = Tracker::getInstance();

    tracker.print_operation(*this, "++");

    return oldValue;
}

template<class T>
const SuperType<T> SuperType<T>::operator--() 
{
    SuperType<T> oldValue(*this);
    value_--;

    Tracker &tracker = Tracker::getInstance();

    tracker.print_operation(*this, "--");
    
    return oldValue;
}

template<class T>
const SuperType<T>& SuperType<T>::operator--(int) 
{
    value_--;

    Tracker &tracker = Tracker::getInstance();

    tracker.print_operation(*this, "--");
    
    return *this;
}