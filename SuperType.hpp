#pragma once

#include "Tracker.hpp"
#include <iostream>
#include <string>


static int number_ = 0;

#define binary_operator(oper, type)                                                             \
SuperType<T> operator oper (const SuperType<T> &that)                                           \
{                                                                                               \
    log_ = false;                                                                               \
                                                                                                \
    SuperType<T> new_that(*this);                                                               \
    new_that oper##= that;                                                                      \
                                                                                                \
    log_ = true;                                                                                \
                                                                                                \
    Tracker &tracker = Tracker::getInstance();                                                  \
                                                                                                \
    tracker.print_operation(*this, that, new_that, type);                \
                                                                                                \
    return new_that;                                                                            \
}                                                                               

#define mono_operator(oper, type)                                                               \
SuperType<T> &operator oper (const SuperType<T> &that)                                          \
{                                                                                               \
                                                                                                \
    value_ oper that.value_;                                                                    \
                                                                                                \
    if (log_ == true)                                                                           \
    {                                                                                           \
        Tracker &tracker = Tracker::getInstance();                                              \
        std::cout << "Operator " << name_ << " " << #oper << " "<<  that.name_ << std::endl;    \
        tracker.print_operation(*this, that, *this, type);                                     \
    }                                                                                           \
                                                                                                \
    return *this;                                                                               \
}

template<class T>
class SuperType
{
public:
    SuperType<T>(const T &value, const std::string &name = "");
    
    SuperType<T>(const SuperType<T> &that, const std::string &name = "");    
    SuperType<T> &operator= (const SuperType<T> &that);

    SuperType<T>(SuperType<T> &&that, const std::string &name = "");
    SuperType<T> &operator= (SuperType<T> &&that);

    // SuperType<T>(SuperType<T> &that, const std::string &name = "");
    // SuperType<T> &operator= (SuperType<T> &that);

    // SuperType<T>(const SuperType<T> &&that, const std::string &name = "");
    // SuperType<T> &operator= (const SuperType<T> &&that);

    ~SuperType<T>();

    mono_operator(+=, MONO_ADD)
    mono_operator(-=, MONO_SUB)
    mono_operator(/=, MONO_DIV)
    mono_operator(*=, MONO_MUL)
    mono_operator(%=, MONO_MOD)
    mono_operator(&=, MONO_AND)
    mono_operator(|=, MONO_OR)
    mono_operator(^=, MONO_DEGREE)

    binary_operator(+, BIN_ADD)
    binary_operator(-, BIN_SUB)
    binary_operator(/, BIN_DIV)
    binary_operator(*, BIN_MUL)
    binary_operator(%, BIN_MOD)
    binary_operator(&, BIN_BIT_AND)
    binary_operator(|, BIN_BIT_OR)
    binary_operator(^, BIN_DEGREE)

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
    
    void rename(const std::string &name)
    {
        name_ = name;
        color_ = "";
        style_ = "";
        
        Tracker &tracker = Tracker::getInstance();
        tracker.print_node(*this);
    }

    const SuperType<T> &operator[] (size_t index) const = delete;
    SuperType<T> &operator[] (size_t index) = delete;

    friend Tracker;
    
private:
    T value_;
    std::string name_;

    int id_ = -1; 

    static bool log_;

    std::string color_ = "";
    std::string style_ = "";
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
        
        style_ = "filled";
        color_ = "#EC7063";
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

        style_ = "filled";
        color_ = "#EC7063";
    }

    if (log_)
    {
        std::cout << "Copy constructor " << name_ << std::endl; 
        
        Tracker &tracker = Tracker::getInstance();
        
        int operation_id = tracker.print_oper(CONSTRUCTOR_COPY, "#EC7063", "filled");

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
        tracker.print_operation(*this, that, *this, EQ_COPY, "#EC7063", "filled");
    }

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

        style_ = "filled";
        color_ = "#58D68D";
    }

    if (log_)
    {
        std::cout << "Copy constructor " << name_ << std::endl; 

        Tracker &tracker = Tracker::getInstance();

        int operation_id = tracker.print_oper(CONSTRUCTOR_MOVE, "#58D68D", "filled");;

        tracker.print_edge(that.id_, operation_id);
        tracker.print_node(*this);
        tracker.print_edge(operation_id, id_);
    }
}

template<class T>
SuperType<T> &SuperType<T>::operator= (SuperType<T> &&that)
{
    if (this != &that)
    {
        this->value_ = that.value_;
        
        if (log_)
        {
            std::cout << "Operator = " << name_ << std::endl; 

            Tracker &tracker = Tracker::getInstance();

            tracker.print_operation(*this, that, *this, EQ_MOVE, "#58D68D", "filled");
        }
    }

    return *this;
}

// template<class T>
// SuperType<T>::SuperType(SuperType<T> &that, const std::string &name): 
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
        
//         int operation_id = tracker.print_oper(" copy", "#EC7063", "filled");

//         tracker.print_edge(that.id_, operation_id);
//         tracker.print_node(*this);
//         tracker.print_edge(operation_id, id_);
//     }
// }

// template<class T>
// SuperType<T> &SuperType<T>::operator= (SuperType<T> &that)
// {
//     this->value_ = that.value_;

//     if (log_)
//     {
//         Tracker &tracker = Tracker::getInstance();

//         std::cout << "Operator = " << name_ << std::endl; 
//         tracker.print_operation(*this, that, *this, "= (copy)", "#EC7063", "filled");
//     }

//     return *this;
// }

// template<class T>
// SuperType<T>::SuperType(const SuperType<T> &&that, const std::string &name): 
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

//         int operation_id = tracker.print_oper("const move", "#EC7063", "filled");;

//         tracker.print_edge(that.id_, operation_id);
//         tracker.print_node(*this);
//         tracker.print_edge(operation_id, id_);
//     }
// }

// template<class T>
// SuperType<T> &SuperType<T>::operator= (const SuperType<T> &&that)
// {
//     if (this != &that)
//     {
//         this->value_ = that.value_;
        
//         if (log_)
//         {
//             std::cout << "Operator = " << name_ << std::endl; 

//             Tracker &tracker = Tracker::getInstance();

//             tracker.print_operation(*this, that, *this, "const = (move)", "#EC7063", "filled");
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