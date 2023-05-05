#include <iostream>
#include <utility>
#include <type_traits>

template <typename T, typename = void>
class SmartPointer;

template <typename T>
class SmartPointer <T, std::enable_if_t<not std::is_pointer_v<T> > >
{
    private:
        T* buff = new T;
};

template <typename T>
class SmartPointer <T, std::enable_if_t<std::is_pointer_v<T> > >
{
    private:
        T* buff = new T[sizeof(*buff)];

};

