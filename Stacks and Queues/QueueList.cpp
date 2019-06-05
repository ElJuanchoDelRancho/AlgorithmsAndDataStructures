/**
    QueueList.cpp
    Purpose: Queue implementation with linked list

    @author: Juan Castillo
    @version: 1.0 04/06/2019
*/

#include <iostream>
#include <exception>

template<class type>
class Node
{
public:
    Node() { next = nullptr; }
    Node(type data) { this->data = data; next = nullptr; }

    type data;
    Node<type>* next;
};

template<class type>
class Queue
{
public:
    Queue();

    void push(const type& value);
    void pop();
    const type& front() const;
    void clear();
    bool empty() const;

    int count;

private:
    Node<type>* head;
    Node<type>* tail;
};

template<class type>
Queue<type>::Queue() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<class type>
void Queue<type>::push(const type& value) {
    Node<type>* temp = new Node<type>(value);
    if (empty() == true) {
        head = temp;
        tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
    count++;
}

template<class type>
void Queue<type>::pop() {
    if (empty() == false) {
        Node<type>* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        count--;
        delete temp;
    }
}

template<class type>
const type& Queue<type>::front() const {
    if (empty() == true) {
        throw std::underflow_error("Queue underflow");
    }
    return head->data;
}

template<class type>
void Queue<type>::clear() {
    while (empty() == false) {
        pop();
    }
}

template<class type>
bool Queue<type>::empty() const {
    return head == nullptr;
}

int main() {
    Queue<int> my_queue;

    my_queue.push(1);
    my_queue.push(2);
    my_queue.push(3);
    my_queue.push(4);
    my_queue.push(5);

    while (my_queue.empty() == false) {
        std::cout << my_queue.front() << ' ';
        my_queue.pop();
    }

    std::cin.get();

    return 0;
}
