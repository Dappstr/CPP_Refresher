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

        Vector(const Vector& vSource) = default;
        Vector(Vector&& vSource) = default;

        const size_t size() noexcept { return m_size; }
        auto begin() noexcept { return &m_buffer[0]; }
        auto end() noexcept { return &m_buffer[m_size-1]; }

        void insert(const auto& element) {
            T* m_newBuff = new T[m_size+1];
            memcpy(m_buffer, m_newBuff, m_size);
            m_size += 1;
            assert(m_size > 0);
            m_newBuff[m_size] = element;
            delete[] m_buffer;
            m_buffer = new T[m_size];
            memcpy(m_newBuff, m_buffer, m_size);
        }

        void insert(auto&& element) {
            T* m_newBuff = new T[m_size+1];
            memcpy(m_buffer, m_newBuff, m_size);
            m_size += 1;
            assert(m_size > 0);
            m_newBuff[m_size] = std::move(element);
            delete[] m_buffer;
            m_buffer = new T[m_size];
            memcpy(m_newBuff, m_buffer, m_size);
        }

        //Operators
        Vector& operator=(const Vector& vSource) = default;
        Vector& operator=(Vector&& vSource) = default;

        std::ostream& operator << (std::ostream& out, Vector<T>& vSource) {
            std::for_each(vSource.begin(), vSource.end(), [&vSource](const auto& element) -> void {
                #if __cplusplus >= 201703L
                if(std::is_pointer_v<T>) { out << *element << ' '; }
                #endif

                #if __cplusplus < 201703L
                if(std::is_pointer<T>::value) { out << *elemennt << ' '; }
                #endif

                else { out << element << ' '; }
            });
            return out;
        }

        ~Vector() {
            m_size = 0;
            delete[] m_buffer;
        }

};
