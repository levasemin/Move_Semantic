# Предисловие
С приходом эры c++11/14 мир кардинально изменился, обычный мир семантики копирования дополнился незримым миром волшебства- семантики перемещения. Задача этой работы заключается в изучении этого мира, прикрытого завесой тайны, и тех, кто в нем обитает. В качестве волшебного инструмента для того, чтобы увидеть
 Задачей этой работы является детальное изучение разницы между семантикой копирования и перемещения с подробной визуализацией библиотеки graphviz.

# Копирование и Перемещение
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
    
    result = c;
    result = func(a, b * c);
    
    end_function();
}
```
    
# Специальный флаг
Оптимизации компилятора позволяют не создавать временный объект, который используется только для инициализации объекта такого же типа. 
Флаг -fno-elide-constructors отключает эту оптимизацию и позволит более детально рассмотреть вызовы конструкторов копирования (перемещения) во всех случаях.

<p>
    <img src="diagrams/graph_no_flag.png" alt="Фотография 1" width="500" height="500">
    <img src="diagrams/graph_flag.png"    alt="Фотография 2" width="499" height="1000">
</p>

# Конструктор и оператор копирования 
Если писать следуя стандартам с++98/03, то мы будем располагать лишь копирующими конструкторами, суть которых заключается в полном копировании классов с их атрибутами.

<p> 
    <img src="diagrams/graph_copy.png"    alt="Фотография 2" width="500" height="1000">
</p>

Полное копирование является ресурсоемкой операцией, поэтому в блок схеме она выделена красным, как нежелательные блоки в программе, хотя в некоторых случаях их избежать нельзя.

# Конструктор и оператор перемещения
В c++11/14 появилась семантика перемещения, дарующя возможность оптимизировать код с помощью идеи обмена атрибутами с умирающими объектами, заменяя собой семантику копирования. Перемещающие конструкторы и операторы присваивания менее ресурсоемкие в сравнении с копирующими, поэтому в блок схеме они горят зеленым, как наиболее желательные для вызова. 

<p>    
    <img src="diagrams/graph_move.png"    alt="Фотография 2" width="500" height="1000">
</p>  

# Сравнение изменений
Несмотря на лучшую производительность компилятор не заменил всю копирующую семантику на перемещающую, так как она становятся альтернативой, только когда речь заходит об объектах типа rvalue, выступающих в роли объектов для инициализации или присваивания. Если внимательно посмотреть на код, то становится ясно, что в некоторых случаях без копирования обойтись нельзя.

<p>
    <img src="diagrams/graph_copy.png" alt="Фотография 1" width="500" height="1000">
    <img src="diagrams/graph_move.png" alt="Фотография 2" width="500" height="1000">
</p>

# Странные вариации семантики копирования и перемещения

## Странные методы копирования

Стандартным способом определения копирующих конструктора и оператора присваивания является такой код:
~~~
SuperType<T>(const SuperType<T> &that, const std::string &name = "");    
SuperType<T> &operator= (const SuperType<T> &that);
~~~
Не смотря на это по ошибке можно задать эти два метода так
~~~
SuperType<T>(SuperType<T> &that, const std::string &name = "");
SuperType<T> &operator= (SuperType<T> &that);
~~~
Единственное, что изменится с неправильным вариантом это отсутствие возможности использования конструктора и оператора с константными объектами. Во время компиляции кода 
```
const SuperType<int> c(20, "c");
SuperType<int> result(c);
```
мы получим ошибку вида 

![](diagrams/copy_сonstructor_error.png)

которая является вполне логичной, тк объект с не является константным. 
Попробовав запустить 
```
const SuperType<int> c(20, "c");
SuperType<int> result(0, "result");
    
result = c;
```
мы получим           
![](diagrams/copy_operator_error.png)

## Странные методы перемещения

Аналогично с кодом для семантики перемещения.
Перемещающие методы обычно выглядят так 
```
SuperType<T>(SuperType<T> &&that, const std::string &name = "");
SuperType<T> &operator= (SuperType<T> &&that);
```
Не смотря на это по ошибке ее можно задать так
```
SuperType<T>(const SuperType<T> &&that, const std::string &name = "");
SuperType<T> &operator= (const SuperType<T> &&that);
```

Код скомпилируется, однако вся магия семантики перемещения улетучится и мы вернемся обратно во времена с++98/03, когда всем миром правила семантика копирования. Причиной станет константность, котороая не позволит выполнить обмен полями и перемещение превратится в копирования. Блок схема в таком случае преобразится.
<p>
    <img src="diagrams/graph_move.png" alt="Фотография 1" width="500" height="1000">
    <img src="diagrams/graph_wrong_move.png"    alt="Фотография 2" width="500" height="1000">
</p>

# Резюмируем
На первый взгляд семантика перемещения может показаться over engineering, так как она применяется не на каждом шагу. Однако на продемонстрированном простом примере можно наблюдать, что она применяется гораздо чаще, чем это может казаться.

# Move vs Forward
Вот мы и добрались до фантастических тварей, пришедших вместе с новым миром move и forward. Главное, что о них стоит сейчас понять, что они ничего не делают.
          move - ничего не перемещает.
          forward - ничего не передает.
Зачем же они нужны, если они "ничего не делают"? Оказывается, это не соввсем так. 
Move выполняет безусловное приведение совего аргумента к rvalue.
```
template <typename T>
decltype(auto) move(T &&param)
{
    using ReturnType = std::remove_reference_t<T>&&;
    return static_cast<ReturnType>(param);
}
```

Forward выполняет приведение при определенных условиях.
```
template <typename T>
T&& forward(std::remove_reference_t<T>& x) noexcept
{
    return static_cast<T &&>(x);
}
```

Разберем простейший пример функции swap.
```
template<class T>
void swap(T &&object1, T &&object2)
{    
    start_function();
    using T_ = std::remove_reference_t<T>;

    T_ temp(object1);
    temp.rename("temp");
    object1 = object2;
    object2 = temp;
    end_function();
}
```
Казалось бы, исследуя мир семантики перемещения и её законов, мы можем решить, что все будет основанно на перемещениях, ибо аргументы функции rvalue. 
![](diagrams/simple_swap.png)

Однако реальность сурова и это не так, но в чем проблема? Где наше волшебство, почему мы снова в мире маглов, а волшебного мира как-бдуто и не было? 
Проблема заключается в том, что аргументы функции ссылки на rvalue, но самими rvalue они не являются. Как же быть? 
Ранее я определил move и forward, и кажется, что наиболее очевидное определение move должно подойти, сняв маску с аргументов.

```
template<class T>
void swap(T &&object1, T &&object2)
{    
    start_function();
    using T_ = std::remove_reference_t<T>;

    T_ temp(move(object1));
    temp.rename("temp");
    object1 = move(object2);
    object2 = move(temp);
    end_function();
}
```

![](diagrams/move_swap.png)
О чудо! Мы снова волшебники, и все работает так, как мы и хотели. Move, кажется, сторонник грубой силы, ее инструмент, волшебная палочка, больше похожа на дубинку и под её влиянием любой станет rvalue. В то же время, написав мини класс Beast с функцией set_lifestyle(), можно подумать, что если натравливать move на все и вся, то везде будет волшебство и счастье.
```
class Beast
{
public:
    SuperType<std::string> lifestyle_;

    Beast() : lifestyle_("not exist") {
        lifestyle_.rename("lifestyle_");
    }

    template<class T>
    void set_lifestyle(T&& lifestyle)
    {
        lifestyle_ = move(lifestyle);
    }
};

```
Однако так ли это? Что будет, если мы напишем вот так?
```
void test_move_forward()
{
    start_function();

    Beast lion;
    lion.set_lifestyle(SuperType<std::string>("predator"));

    SuperType<std::string> victim("victim");
    
    Beast sheep;
    sheep.set_lifestyle(victim);
    Beast cow;
    cow.set_lifestyle(victim);

    end_function();
}
```
Вжух! 
![](diagrams/move_beast.png)
И мы разбились о собственное мировоззрение, кажется, что move переборщивает с прибабахом. Неужели придется запереть move до лучших времен очевидного swap, а самим сидеть в скучном мире копирования...
И тут из леса выходит новый зверь, forward...
Однако остается вопрос, что такое функция forward? Ранее было сказано, что у нее какое-то условное приведение и блаблабла.
```
class Beast
{
public:
    SuperType<std::string> lifestyle_;

    Beast() : lifestyle_("not exist") {
        lifestyle_.rename("lifestyle_");
    }

    template<class T>
    void set_lifestyle(T&& lifestyle)
    {
        lifestyle_ = std::forward(lifestyle);
    }
};
```
![](diagrams/forward_beast.png)
О чудо! Мы остались волшебниками и всё работает так, как мы... Хотели? Да, мы этого хотели, но кто такой forward, и почему он нам помог? Оказывается, что forward приводит условное приведение, rvalue к rvalue, lvalue к lvalue. 
В таком случае может показаться, что мы нашли универсальный способ решения всех наших проблем, быть может, это наш философский камень. С технической точки зрения ответ утвердительный: forward может сделать все, необходимости в move нет.

