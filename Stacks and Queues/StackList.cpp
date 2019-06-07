/**
    StackList.cpp
    Purpose: Stack implementation with linked list

    @author: Juan Castillo
    @version: 1.1 07/06/2019
*/

#include <iostream>
#include <exception>

template<class type>
class Node
{
public:
    Node() { next = nullptr; }
    Node(const type& data) { this->data = data; next = nullptr; }

    type data;
    Node<type>* next;
};

template<class type>
class Stack
{
public:
    Stack();

    void push(const type& value);
    void pop();
    const type& peek() const;
    void clear();
    bool empty() const;

    int count;

private:
    Node<type>* top;
};

template<class type>
Stack<type>::Stack() {
    top = nullptr;
    count = 0;
}

template<class type>
void Stack<type>::push(const type& value) {
    Node<type>* temp = new Node<type>(value);
    temp->next = top;
    top = temp;
    count++;
}

template<class type>
void Stack<type>::pop() {
    if (empty() == false) {
        Node<type>* temp = top;
        top = top->next;
        count--;
        delete temp;
    }
}

template<class type>
const type& Stack<type>::peek() const {
    if (empty() == true) {
        throw std::underflow_error("Stack underflow");
    }
    return top->data;
}

template<class type>
void Stack<type>::clear() {
    while (empty() == false) {
        pop();
    }
}

template<class type>
bool Stack<type>::empty() const {
    return top == nullptr;
}

int main() {
    Stack<int> my_stack;

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
