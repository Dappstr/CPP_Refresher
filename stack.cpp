#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

template <typename T>
concept acceptableType =
                        std::is_move_constructible_v<std::decay_t<T>> &&
                        std::is_copy_constructible_v<std::decay_t<T>> && 
                        std::is_copy_assignable_v<std::decay_t<T>> &&
                        std::is_move_assignable_v<std::decay_t<T>>;

template <acceptableType T>
//requires std::is_move_constructible_v<std::decay_t<T>> && std::is_copy_constructible_v<std::decay_t<T>>
class Stack
{
    private:
        std::vector<T> m_stack{};

    protected:
        void insertElement(const T& val) const {
            m_stack.push_back(val);
        }

        void insertElement(T&& val) {
            m_stack.push_back(std::move(val));
        }

    public:
        Stack() = default;
        Stack(std::initializer_list<T> list) {
            std::for_each(list.begin(), list.end(), 
            [&list, this](T val) mutable {
                m_stack.push_back(std::move(val));
            });
        }
        Stack(T val) {
            m_stack.push_back(val);
        }

        Stack(const Stack& src) {
            std::copy(src.m_stack.begin(), src.m_stack.end(), std::back_inserter(m_stack));
        }
        Stack& operator=(const Stack& src) {
            std::copy(src.m_stack.begin(), src.m_stack.end(), std::back_inserter(m_stack));
        }

        Stack(Stack&& src) = default;
        Stack& operator=(Stack&& src) = default;

        inline size_t size() noexcept(noexcept(m_stack.size() >= 0)) { 
            return m_stack.size();
        }

        void push(T val) {
            insertElement(std::forward<T>(val));
        }

        T pop() {
            assert(m_stack.size() > 0);
            T value = m_stack.back();
            m_stack.pop_back();
            return value;
        }

        const T& top() const {
            return m_stack.back();
        }

        bool empty() {
            return m_stack.empty();
        }

        T operator[](size_t index) noexcept(noexcept(index >= 0)) {
            return m_stack.at(index);
        }

        const T operator[](size_t index) const noexcept(noexcept(index >= 0)) {
            return m_stack.at(index);
        }

        friend std::ostream& operator<<(std::ostream& out, Stack<T>& stack) {
            for(size_t i = 0; i < static_cast<size_t>(stack.size()); ++i) {
                out << stack[i] << ' ';
            }
            return out;
        }

        void operator<<(const Stack& stack) const {
            for(size_t i = 0; i < static_cast<size_t>(m_stack.size()); ++i) {
                std::cout << stack[i] << ' ';
            }
        }

        bool operator==(Stack<T>& rhs) {
            return std::equal(m_stack.begin(), m_stack.end(), rhs.m_stack.begin(), rhs.m_stack.end());
            //assert(m_stack.size() == rhs.size());

            /*
            Manual way
            if(m_stack.size() != rhs.size()) { return false;}

            for(size_t i = 0; i < m_stack.size(); ++i) {
                if(m_stack[i] != rhs[i]) { return false;}
            }
            
            return true;
            */
        }

        ~Stack() = default;
};
