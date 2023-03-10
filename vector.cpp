//WIP
#include <iostream>

template <typename T, size_t N = 0>
class Vector {
    private:
        T* m_buffer = nullptr;
        size_t m_size {N};

    public:
        Vector<T>(size_t n) {
            m_buffer = new T[n];
        }

        Vector<T>(const Vector<T>& vSource) = default;
        Vector<T>(Vector<T>&& vSource) = default;

        const size_t size() noexcept { return m_size; }

        //Return the address of the first index assuming that the object is valid.
        auto begin() noexcept(noexcept(m_size >= 0)) {
            assert(std::addressof(m_buffer[0]) != NULL);
            return &m_buffer[0];
        } 

        //Return the address of the last index
        auto end() noexcept(noexcept(m_size >= 0)) {
            assert(m_size >= 0);
            return &m_buffer[m_size-1];    
        }

        /*
        For inserting, essentially create a new buffer of identical elements with a larger size, and then replace the current buffer with that one.
        Probably better way to do this, however this is just more convenient.
        Will possibly change/improve in the future.
        */
        void insert(const auto& element) {
            T* newBuff = new T[m_size+1];
            memcpy(m_buffer, newBuff, m_size);
            m_size += 1;
            assert(m_size > 0);
            newBuff[m_size] = element;
            delete[] m_buffer;
            m_buffer = new T[m_size];
            memcpy(newBuff, m_buffer, m_size);
            delete[] newBuff;
        }

        void insert(auto&& element) {
            T* newBuff = new T[m_size+1];
            memcpy(m_buffer, newBuff, m_size);
            m_size += 1;
            assert(m_size > 0);
            newBuff[m_size] = std::move(element);
            delete[] m_buffer;
            m_buffer = new T[m_size];
            memcpy(newBuff, m_buffer, m_size);
            delete[] newBuff;
        }

        //Operators
        Vector& operator=(const Vector<T>& vSource) = default;
        Vector& operator=(Vector<T>&& vSource) = default;

        friend std::ostream& operator << (std::ostream& out, Vector<T>& vSource) {
            std::for_each(vSource.begin(), vSource.end(), [&vSource, &out](const auto& element) -> void {
                //Check for C++ standard for appropriate type checking for pointer types. If type is pointer, stream the dereferenced value.
                #if __cplusplus >= 201703L
                if(std::is_pointer_v<T>) { out << *element << ' '; }

                #elif __cplusplus < 201703L
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
