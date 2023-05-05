// Requires C++17 support

#include <iostream>
#include <utility>
#include <type_traits>

#if __cplusplus < 201703L
    #error "Invalid C++ standard, please use C++17 or later"
#endif

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

