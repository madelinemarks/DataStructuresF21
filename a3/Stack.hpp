using namespace std;

template <typename T>
Stack<T>::Stack()
{
}

template <typename T>
Stack<T>::~Stack()
{
    stack.clear();
}

template <typename T>
Stack<T>::Stack(const Stack<T> &rhs)
{
    stack = rhs.stack;
}

template <typename T>
Stack<T>::Stack(Stack<T> &&rhs)
{
    std::swap(*this, rhs);
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &rhs)
{
    stack = rhs.stack;
    return *this;
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&rhs)
{
    std::swap(*this, rhs);
    return *this;
}

template <typename T>
bool Stack<T>::empty() const
{
    return stack.empty();
}

template <typename T>
T& Stack<T>::top()
{
    return stack.back();
}

template <typename T>
const T& Stack<T>::top() const
{
    return stack.back();
}

template <typename T>
void Stack<T>::pop()
{
    stack.pop_back();
}

template <typename T>
void Stack<T>::push(const T& val)
{
    stack.push_back(val);
}

template <typename T>
void Stack<T>::push(T&& val)
{
    stack.push_back(move(val));
}

template <typename T>
int Stack<T>::size() const
{
    return stack.size();
}
