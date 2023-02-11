# Копирование и Перемещение
Задачей этой работы является детальное изучение разницы между семантикой копирования и перемещения с подробной визуализацией библиотеки graphviz.
Блок схемы построены на основе незамысловатого кода

```
#include "SuperType.hpp"
          
#define start_function() Tracker::getInstance().print_open_func(__func__);
#define end_function()   Tracker::getInstance().print_close_func(__func__);

template<class T>
SuperType<T> func(SuperType<T> a, SuperType<T> b)
{
    start_function()
    SuperType<int> c = a + b;
    end_function()
    return c;
}

int main()
{
    start_function();
    
    SuperType<int> a(5,  "a");
    SuperType<int> b(14, "b");
    SuperType<int> c(20, "c");
    SuperType<int> result(0, "result");
    
    result = func(a * c, b - c);
    
    end_function();
}
```
    
# Специальный флаг
Оптимизации компилятора позволяют не создавать временный объект, который используется только для инициализации объекта такого же типа. 
Флаг -fno-elide-constructors отключает эту оптимизацию и позволит более детально рассмотреть вызовы конструкторов копирования (перемещения) во всех случаях.

<p>
    <img src="images/graph_no_flag.png" alt="Фотография 1" width="400" height="400" class="">
    <img src="images/graph_flag.png"    alt="Фотография 2" width="400" height="800">
</p>

#Конструктор копирования 
