#pragma once

#include <iostream>
#include <string>

#include "Tracker.hpp"

namespace SL
{

static int number_ = 0;

const std::string none    = "";
const std::string red     = "#EC7063";
const std::string green   = "#58D68D";

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
    tracker.print_operation(*this, that, new_that, {"", "", tracker.get_operation_name(type)}); \
                                                                                                \
    return new_that;                                                                            \
}                                                                               

#define mono_operator(oper, type)                                                                               \
SuperType<T> &operator oper (const SuperType<T> &that)                                                          \
{                                                                                                               \
                                                                                                                \
    value_ oper that.value_;                                                                                    \
                                                                                                                \
    if (log_ == true)                                                                                           \
    {                                                                                                           \
        Tracker &tracker = Tracker::getInstance();                                                              \
        tracker.print_operation(*this, that, *this, {"", "", tracker.get_operation_name(type)});                \
    }                                                                                                           \
                                                                                                                \
    return *this;                                                                                               \
}

template<class T>
class SuperType
{
public:
    SuperType<T>(const T &value);

#ifndef WRONG_COPY_SEMANTIC
    SuperType<T>(const SuperType<T> &that);    
    SuperType<T> &operator= (const SuperType<T> &that);
#endif

#ifdef MOVE_SEMANTIC
    SuperType<T>(SuperType<T> &&that);
    SuperType<T> &operator= (SuperType<T> &&that);
#endif

#ifdef WRONG_COPY_SEMANTIC
    SuperType<T>(SuperType<T> &that);    
    SuperType<T> &operator= (SuperType<T> &that);
#endif

#ifdef WRONG_MOVE_SEMANTIC
    SuperType<T>(const SuperType<T> &&that);
    SuperType<T> &operator= (const SuperType<T> &&that);
#endif

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

    SuperType<T>  operator++(int);
    SuperType<T> &operator++();
    SuperType<T>  operator--(int);
    SuperType<T>  &operator--();

    operator T() const
    {
        return value_;
    }
    
    void rename(const std::string &name)
    {
        style_.label_ = name;
        
        Tracker &tracker = Tracker::getInstance();
        tracker.print_node(*this);
    }

    const SuperType<T> &operator[] (size_t index) const = delete;
    SuperType<T> &operator[] (size_t index) = delete;

    friend Tracker;

private:
    T value_;
    int id_ = -1; 
    static bool log_;
    style_params style_;
};      

template<class T>
bool SuperType<T>::log_ = true;

template<class T>
SuperType<T>::SuperType(const T &value): value_(value), style_({})
{
    style_.label_ = "tmp" + std::to_string(number_);
    number_++;
        
    if (log_)
    {
        //std::cout << "Constructor " << style_.label_ << std::endl;

        Tracker &tracker = Tracker::getInstance();
        tracker.print_node(*this);
    }
}

#ifndef WRONG_COPY_SEMANTIC
template<class T>
SuperType<T>::SuperType(const SuperType<T> &that): value_(that.value_), style_({})
{
    style_.label_ = "tmp" + std::to_string(number_);
    number_++;

    if (log_)
    {
        //std::cout << "Copy constructor " << style_.label_ << std::endl; 
        
        Tracker &tracker = Tracker::getInstance();
        
        style_params operation_style = {red, "filled", tracker.get_operation_name(CONSTRUCTOR_COPY)};

        tracker.print_operation(*this, that, *this, operation_style);
    }
}

template<class T>
SuperType<T> &SuperType<T>::operator= (const SuperType<T> &that)
{
    this->value_ = that.value_;

    if (log_)
    {
        Tracker &tracker = Tracker::getInstance();

        style_params operation_style = {red, "filled", tracker.get_operation_name(EQ_COPY)};

        //std::cout << "Operator = " << style_.label_ << std::endl; 
        tracker.print_operation(*this, that, *this, operation_style);
    }

    return *this;
}
#endif

#if defined(MOVE_SEMANTIC)
template<class T>
SuperType<T>::SuperType(SuperType<T> &&that): value_(std::move(that.value_)), style_({})
{    
    style_.label_ = "tmp" + std::to_string(number_);
    number_++;

    if (log_)
    {
        //std::cout << "MOVE constructor " << style_.label_ << std::endl; 

        Tracker &tracker = Tracker::getInstance();
        
        style_params operation_style = {green, "filled", tracker.get_operation_name(CONSTRUCTOR_MOVE)};

        tracker.print_operation(*this, that, *this, operation_style);
    }
}

template<class T>
SuperType<T> &SuperType<T>::operator= (SuperType<T> &&that)
{
    if (this != &that)
    {
        this->value_ = SL::move(that.value_);
        
        if (log_)
        {
            //std::cout << "Operator = " << style_.label_ << std::endl; 

            Tracker &tracker = Tracker::getInstance();
            style_params operation_style = {green, "filled", tracker.get_operation_name(EQ_MOVE)};
            tracker.print_operation(*this, that, *this, operation_style);
        }
    }

    return *this;
}
#endif 


#ifdef WRONG_COPY_SEMANTIC
template<class T>
SuperType<T>::SuperType(SuperType<T> &that): value_(that.value_), style_({})
{
    style_.label_ = "tmp" + std::to_string(number_);
    number_++;

    if (log_)
    {
        //std::cout << "Copy constructor " << style_.label_ << std::endl; 
        
        Tracker &tracker = Tracker::getInstance();
        
        style_params operation_style = {red, "filled", tracker.get_operation_name(CONSTRUCTOR_COPY)};

        tracker.print_operation(*this, that, *this, operation_style);
    }
}

template<class T>
SuperType<T> &SuperType<T>::operator= (SuperType<T> &that)
{
    this->value_ = that.value_;

    if (log_)
    {
        Tracker &tracker = Tracker::getInstance();

        style_params operation_style = {red, "filled", tracker.get_operation_name(EQ_COPY)};

        //std::cout << "Operator = " << style_.label_ << std::endl; 
        tracker.print_operation(*this, that, *this, operation_style);
    }

    return *this;
}
#endif


#ifdef WRONG_MOVE_SEMANTIC
template<class T>
SuperType<T>::SuperType(const SuperType<T> &&that): value_(that.value_), style_({})
{    
    style_.label_ = "tmp" + std::to_string(number_);
    number_++;

    if (log_)
    {
        //std::cout << "Copy constructor " << style_.label_ << std::endl; 

        Tracker &tracker = Tracker::getInstance();
        
        style_params operation_style = {red, "filled", tracker.get_operation_name(CONSTRUCTOR_MOVE)};
        tracker.print_operation(*this, that, *this, operation_style);
    }
}

template<class T>
SuperType<T> &SuperType<T>::operator= (const SuperType<T> &&that)
{
    if (this != &that)
    {
        this->value_ = that.value_;
        
        if (log_)
        {
            //std::cout << "Operator = " << style_.label_ << std::endl; 

            Tracker &tracker = Tracker::getInstance();
            style_params operation_style = {red, "filled", tracker.get_operation_name(EQ_MOVE)};
            tracker.print_operation(*this, that, *this, operation_style);
        }
    }

    return *this;
}
#endif


template<class T>
SuperType<T>::~SuperType<T>()
{
    Tracker &tracker = Tracker::getInstance();
    tracker.print_destructor(*this, {"black", "filled", "Destructor", "white"});
    //std::cout << "Destructor " << style_.label_ << std::endl;
}    

template<class T>
void *SuperType<T>::operator new (size_t bytes, bool log_mode)
{
    if (log_mode)
    {
        //std::cout << "Allocated " << bytes << " bytes by new" << std::endl;
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
        //std::cout << "Allocated " << bytes << " bytes by new[]" << std::endl;
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
        //std::cout << "Replacemented " << bytes << " bytes by new" << std::endl;
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
        //std::cout << "Replacemented " << bytes << " bytes by new[]" << std::endl;
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
        //std::cout << "Deallocated " << bytes << " bytes by delete" << std::endl;
    }

    free(pointer);   
}

template<class T>
void SuperType<T>::operator delete[] (void *pointer, size_t bytes)
{
    bool log_mode = true;

    if (log_mode)
    {
        //std::cout << "Deallocated " << bytes << " bytes by delete[]" << std::endl;
    }

    free(pointer);
}


template<class T>
SuperType<T> SuperType<T>::operator++(int) 
{
    value_++;

    Tracker &tracker = Tracker::getInstance();

    tracker.print_operation(*this, INC);
    
    return *this;
}

template<class T>
SuperType<T> &SuperType<T>::operator++() 
{
    SuperType<T> oldValue(*this);
    value_++;

    Tracker &tracker = Tracker::getInstance();

    tracker.print_operation(*this, INC);

    return oldValue;
}

template<class T>
SuperType<T> &SuperType<T>::operator--() 
{
    SuperType<T> oldValue(*this);
    value_--;

    Tracker &tracker = Tracker::getInstance();

    tracker.print_operation(*this, DEC);
    
    return oldValue;
}

template<class T>
SuperType<T> SuperType<T>::operator--(int) 
{
    value_--;

    Tracker &tracker = Tracker::getInstance();

    tracker.print_operation(*this, DEC);
    
    return *this;
}

};