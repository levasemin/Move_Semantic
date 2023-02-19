template<class T>
void forward_swap(T &&object1, T &&object2)
{    
    start_function();
    using T_ = std::remove_reference_t<T>;

    T_ temp(forward<T_>(object1));
    temp.rename("temp");
    object1 = forward<T_>(object2);
    object2 = forward<T_>(temp);
    end_function();
}

template<class T>
void simple_swap(T &&object1, T &&object2)
{    
    start_function();
    using T_ = std::remove_reference_t<T>;

    T_ temp(object1);
    temp.rename("temp");
    object1 = object2;
    object2 = temp;
    end_function();
}