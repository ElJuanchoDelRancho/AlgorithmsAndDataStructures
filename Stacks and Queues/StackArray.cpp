/**
    StackArray.cpp
    Purpose: Stack implementation with array

    @author: Juan Castillo
    @version: 1.0 04/06/2019
*/

#include <iostream>
#include <exception>

template<class type, int max_size>
class Stack
{
public:
    Stack();

    void push(const type& value);
    void pop();
    const type& peek() const;
    void clear();
    bool empty() const;
    bool full() const;

    int count;

private:
    type arr[max_size];
    int top;
};

template<class type, int max_size>
Stack<type, max_size>::Stack() {
    count = 0;
    top = -1;
}

template<class type, int max_size>
void Stack<type, max_size>::push(const type& value) {
    if (full() == false) {
        top++;
        count++;
        arr[top] = value;
    }
}

template<class type, int max_size>
void Stack<type, max_size>::pop() {
    if (empty() == false) {
        top--;
        count--;
    }
}

template<class type, int max_size>
const type& Stack<type, max_size>::peek() const {
    if (empty() == true) {
        throw std::underflow_error("Stack underflow");
    }
    return arr[top];
}

template<class type, int max_size>
void Stack<type, max_size>::clear() {
    top = -1;
    count = 0;
}

template<class type, int max_size>
bool Stack<type, max_size>::empty() const {
    return top == -1;
}

template<class type, int max_size>
bool Stack<type, max_size>::full() const {
    return top == max_size - 1;
}

int main() {
    Stack<int, 10> my_stack;

    my_stack.push(1);
    my_stack.push(2);
    my_stack.push(3);
    my_stack.push(4);
    my_stack.push(5);

    while (my_stack.empty() == false) {
        std::cout << my_stack.peek() << ' ';
        my_stack.pop();
    }

    std::cin.get();

    return 0;
}
