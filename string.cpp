#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class String
{
    private:
        unsigned int m_size{};
        char* m_buffer{};
    
    public:
        String() {
            m_size = 0;
            m_buffer = nullptr;
        }

        String(const char* str)
            :m_size(strlen(str)) {
                delete[] m_buffer;
                m_buffer = new char [m_size+1];
                strcpy(m_buffer, str);
                m_buffer[m_size+1] = '\0';
        }

        String(const String& src)
            :m_size(strlen(src.m_buffer)) {
                delete[] m_buffer;
                m_buffer = new char[m_size+1];
                memcpy(m_buffer, src.m_buffer, m_size);
                m_buffer[m_size+1] = '\0';
        }

        String(String&& src) noexcept
            :m_size(std::move(src.m_size)), m_buffer(std::move(src.m_buffer)) {
                src.m_size = 0;
                src.m_buffer = nullptr;
        }

        String& operator=(const String& src) {
            if(this == &src) {
                return *this;
            }
            delete[] m_buffer;
            
            m_size = src.m_size;
            m_buffer = new char[m_size+1];
            memcpy(m_buffer, src.m_buffer, m_size);
            m_buffer[m_size+1] = '\0';

            return *this;
        }

        String& operator=(String&& src) noexcept {
            if(this == &src) {
                return *this;
            }
            m_size = std::move(src.m_size);
            m_buffer = std::move(src.m_buffer);
            
            src.m_size = 0;
            src.m_buffer = nullptr;
            
            return *this;
        }

        size_t size() noexcept {
            return strlen(m_buffer);
        }

        friend std::ostream& operator<<(std::ostream& out, const String& str);
        char& operator[](size_t indx) noexcept(noexcept(indx >= 0 && indx < this->size())) {
            return m_buffer[indx];
        }

        ~String() {
            delete[] m_buffer;
        }
};

std::ostream& operator<<(std::ostream& out, const String& str) {
    out << str.m_buffer;
    return out;
}
