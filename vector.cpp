//WIP
#include <iostream>

template <typename T, size_t N = 0>
class Vector {
    private:
        T* m_buffer = nullptr;
        size_t m_size {N};

    public:
        Vector(size_t n) {
            m_buffer = new T[N];
        }

        size_t size() { return m_size; }
        auto begin() { return &m_buffer[0]; }
        auto end() { return &m_buffer[m_size-1]; }

        ~Vector() {
            m_size = 0;
            delete[] m_buffer;
        }

}
