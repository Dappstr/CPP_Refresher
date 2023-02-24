#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Stack
{
    private:
        std::vector<T> m_stack{};
    public:
        Stack() = default;
        Stack(std::initializer_list<T> list) {
            std::for_each(list.begin(), list.end(), 
            [&list, this](T val) mutable {
                m_stack.push_back(std::move(val));
            });
        }
        explicit Stack(T val) {
            m_stack.push_back(val);
        }

        Stack(const Stack& src) = default;
        Stack(Stack&& src) = default;

        Stack<T>& operator=(const Stack& src) = default;
        Stack<T>& operator=(Stack&& src) = default;

        inline size_t size() noexcept(noexcept(m_stack.size() >= 0)){ 
            return m_stack.size();
        }

        T operator[](size_t index) noexcept(noexcept(index >= 0)){
            return m_stack.at(index);
        }
        friend std::ostream& operator<<(std::ostream& out, Stack& stack);

        ~Stack() = default;
};

std::ostream& operator<<(std::ostream& out, Stack<int>& stack)
{
    for(auto i = 0; i < static_cast<int>(stack.size()); ++i) {
        out << stack[i] << ' ';
    }
    return out;
}

int main()
{
    Stack<int> stack{2, 5, 3, 7, 8};
    std::cout << stack;

    return 0;
}
