/**
    SinglyLinkedList.cpp
    Purpose: Singly Linked List implementation in C++

    @author: Juan Castillo
    @version: 1.0 02/06/2019
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
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    const type& front() const;
    const type& back() const;
    void push_front(const type& value);
    void push_back(const type& value);
    bool insert_before(const type& key, const type& value);
    bool insert_after(const type& key, const type& value);
    void pop_front();
    void pop_back();
    const type& operator[](int index);
    type& operator[](int index) const;
    bool erase(const type& value);
    bool empty() const;
    void clear();

    int count;

private:
    Node<type>* head;
};

template<class type>
LinkedList<type>::LinkedList() {
    head = nullptr;
    count = 0;
}

template<class type>
LinkedList<type>::~LinkedList() {
    clear();
}

template<class type>
const type& LinkedList<type>::front() const {
    if (empty() == true) {
        throw std::underflow_error("List is empty");
    }
    return head->data;
}

template<class type>
const type& LinkedList<type>::back() const {
    if (empty() == true) {
        throw std::underflow_error("List is empty");
    }
    Node<type>* aux = head;
    while (aux->next != nullptr) {
        aux = aux->next;
    }
    return aux->data;
}

template<class type>
void LinkedList<type>::push_front(const type& value) {
    Node<type>* temp = new Node<type>(value);
    temp->next = head;
    head = temp;
    count++;
}

template<class type>
void LinkedList<type>::push_back(const type& value) {
    Node<type>* temp = new Node<type>(value);
    if (head == nullptr) {
        head = temp;
    } else {
        Node<type>* aux = head;
        while (aux->next != nullptr) {
            aux = aux->next;
        }
        aux->next = temp;
    }
    count++;
}

template<class type>
bool LinkedList<type>::insert_before(const type& key, const type& value) {
    Node<type>* before;
    Node<type>* current = head;
    while (current != nullptr && current->data != key) {
        before = current;
        current = current->next;
    }
    if (current == nullptr) {
        return false;
    }
    Node<type>* temp = new Node<type>(value);
    temp->next = current;
    if (current == head) {
        head = temp;
    } else {
        before->next = temp;
    }
    count++;
    return true;
}

template<class type>
bool LinkedList<type>::insert_after(const type& key, const type& value) {
    Node<type>* aux = head;
    while (aux != nullptr && aux->data != key) {
        aux = aux->next;
    }
    if (aux == nullptr) {
        return false;
    }
    Node<type>* temp = new Node<type>(value);
    temp->next = aux->next;
    aux->next = temp;
    count++;
}

template<class type>
void LinkedList<type>::pop_front() {
    if (head != nullptr) {
        Node<type>* temp = head;
        head = head->next;
        count--;
        delete temp;
    }
}

template<class type>
void LinkedList<type>::pop_back() {
    if (head != nullptr) {
        Node<type>* aux = head;
        while (aux->next != nullptr) {
            aux = aux->next;
        }
        Node<type>* temp = aux;
        aux = nullptr;
        count--;
        delete temp;
    }
}

template<class type>
const type& LinkedList<type>::operator[](int index) {
    if (index < 0 || index >= count) {
        throw std::invalid_argument("Invalid index");
    }
    Node<type>* aux = head;
    int aux_index = 0;
    while (aux_index < index) {
        ++aux_index;
        aux = aux->next;
    }
    return aux->data;
}

template<class type>
type& LinkedList<type>::operator[](int index) const {
    if (index < 0 || index >= count) {
        throw std::invalid_argument("Invalid index");
    }
    Node<type>* aux = head;
    int aux_index = 0;
    while (aux_index < index) {
        ++aux_index;
        aux = aux->next;
    }
    return aux->data;
}

template<class type>
bool LinkedList<type>::erase(const type& value) {
    Node<type>* before;
    Node<type>* current = head;
    while (current != nullptr && current->data != value) {
        before = current;
        current = current->next;
    }
    if (current == nullptr) {
        return false;
    }
    if (current == head) {
        head = head->next;
    } else {
        before->next = current->next;
    }
    count--;
    delete current;
    return true;
}

template<class type>
bool LinkedList<type>::empty() const {
    return head == nullptr;
}

template<class type>
void LinkedList<type>::clear() {
    while (empty() == false) {
        pop_front();
    }
}

int main() {
    LinkedList<int> my_list;

    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);
    my_list.push_back(5);
    my_list.push_back(6);

    for (int i = 0; i < my_list.count; i++) {
        std::cout << my_list[i] << " ";
    }
    std::cout << std::endl;
    std::cin.get();

    return 0;
}
