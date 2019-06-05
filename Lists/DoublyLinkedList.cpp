/**
    DoublyLinkedList.cpp
    Purpose: Doubly Linked List implementation in C++

    @author: Juan Castillo
    @version: 1.0 04/06/2019
*/

#include <iostream>
#include <exception>

template<class type>
class Node
{
public:
    Node() { next = nullptr; prev = nullptr; }
    Node(type data) { this->data = data; next = nullptr; prev = nullptr; }

    type data;
    Node<type>* next;
    Node<type>* prev;
};

template<class type>
class DLinkedList
{
public:
    DLinkedList();
    ~DLinkedList();

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
    void print() {
        Node<type>* temp = head;
        while (temp->next != nullptr) {
            std::cout << temp->data << ' ';
            temp = temp->next;
        }
        std::cout << temp->data << '\n';
        while (temp != nullptr) {
            std::cout << temp->data << ' ';
            temp = temp->prev;
        }
        std::cout << '\n';
    }

    int count;

private:
    Node<type>* head;
};

template<class type>
DLinkedList<type>::DLinkedList() {
    head = nullptr;
    count = 0;
}

template<class type>
DLinkedList<type>::~DLinkedList() {
    clear();
}

template<class type>
const type& DLinkedList<type>::front() const {
    if (empty() == true) {
        throw std::underflow_error("List is empty");
    }
    return head->data;
}

template<class type>
const type& DLinkedList<type>::back() const {
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
void DLinkedList<type>::push_front(const type& value) {
    Node<type>* temp = new Node<type>(value);
    temp->next = head;
    if (head != nullptr) {
        head->prev = temp;
    }
    head = temp;
    count++;
}

template<class type>
void DLinkedList<type>::push_back(const type& value) {
    Node<type>* temp = new Node<type>(value);
    if (head == nullptr) {
        head = temp;
    } else {
        Node<type>* aux = head;
        while (aux->next != nullptr) {
            aux = aux->next;
        }
        aux->next = temp;
        temp->prev = aux;
    }
    count++;
}

template<class type>
bool DLinkedList<type>::insert_before(const type& key, const type& value) {
    Node<type>* current = head;
    while (current != nullptr && current->data != key) {
        current = current->next;
    }
    if (current == nullptr) {
        return false;
    }
    Node<type>* temp = new Node<type>(value);
    temp->next = current;
    temp->prev = current->prev;
    if (current == head) {
        head->prev = temp;
        head = temp;
    } else {
        current->prev->next = temp;
        current->prev = temp;
    }
    count++;
    return true;
}

template<class type>
bool DLinkedList<type>::insert_after(const type& key, const type& value) {
    Node<type>* aux = head;
    while (aux != nullptr && aux->data != key) {
        aux = aux->next;
    }
    if (aux == nullptr) {
        return false;
    }
    Node<type>* temp = new Node<type>(value);
    temp->next = aux->next;
    temp->prev = aux;
    if (aux->next != nullptr) {
        aux->next->prev = temp;
    }
    aux->next = temp;
    count++;
    return true;
}

template<class type>
void DLinkedList<type>::pop_front() {
    if (head != nullptr) {
        Node<type>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        count--;
        delete temp;
    }
}

template<class type>
void DLinkedList<type>::pop_back() {
    if (head != nullptr) {
        Node<type>* aux = head;
        while (aux->next != nullptr) {
            aux = aux->next;
        }
        Node<type>* temp = aux;
        if (aux == head) {
            head = nullptr;
        } else {
            aux->prev->next = nullptr;
        }
        count--;
        delete temp;
    }
}

template<class type>
const type& DLinkedList<type>::operator[](int index) {
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
type& DLinkedList<type>::operator[](int index) const {
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
bool DLinkedList<type>::erase(const type& value) {
    Node<type>* current = head;
    while (current != nullptr && current->data != value) {
        current = current->next;
    }
    if (current == nullptr) {
        return false;
    }
    if (current == head) {
        head = head->next;
        head->prev = nullptr;
    } else if (current->next == nullptr) {
        current->prev->next = nullptr;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    count--;
    delete current;
    return true;
}

template<class type>
bool DLinkedList<type>::empty() const {
    return head == nullptr;
}

template<class type>
void DLinkedList<type>::clear() {
    while (empty() == false) {
        pop_front();
    }
}

int main() {
    DLinkedList<int> my_list;

    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);
    my_list.push_back(5);
    my_list.push_back(6);

    my_list.erase(3);

    /*for (int i = 0; i < my_list.count; i++) {
        std::cout << my_list[i] << " ";
    }*/

    my_list.print();

    std::cout << std::endl;
    std::cin.get();

    return 0;
}
