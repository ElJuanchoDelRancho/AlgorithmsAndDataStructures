/**
    QueueArray.cpp
    Purpose: Queue implementation with array

    @author: Juan Castillo
    @version: 1.0 04/06/2019
*/

#include <iostream>
#include <exception>

template<class type, int max_size>
class Queue
{
public:
    Queue();

    void push(const type& value);
    void pop();
    const type& front() const;
    void clear();
    bool empty() const;
    bool full() const;

    int count;

private:
    type arr[max_size];
    int tail;
};

template<class type, int max_size>
Queue<type, max_size>::Queue() {
    tail = -1;
    count = 0;
}

template<class type, int max_size>
void Queue<type, max_size>::push(const type& value) {
    if (full() == false) {
        tail++;
        count++;
        arr[tail] = value;
    }
}

template<class type, int max_size>
void Queue<type, max_size>::pop() {
    if (empty() == false) {
        for (int i = 0; i < tail; i++) {
            arr[i] = arr[i + 1];
        }
        tail--;
        count--;
    }
}

template<class type, int max_size>
const type& Queue<type, max_size>::front() const {
    if (empty() == true) {
        throw std::underflow_error("Queue underflow");
    }
    return arr[0];
}

template<class type, int max_size>
void Queue<type, max_size>::clear() {
    tail = -1;
    count = 0;
}

template<class type, int max_size>
bool Queue<type, max_size>::empty() const {
    return tail == -1;
}

template<class type, int max_size>
bool Queue<type, max_size>::full() const {
    return tail == max_size - 1;
}

int main() {
    Queue<int, 10> my_queue;

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
