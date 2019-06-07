/**
    CircularDoublyLinkedList.cpp
    Purpose: Circular Doubly Linked List implementation in C++

    @author: Juan Castillo
    @version: 1.1 07/06/2019
*/

#include <iostream>
#include <exception>

template<class type>
class Node
{
public:
    Node() { next = this; prev = this; }
    Node(const type& data) { this->data = data; next = this; prev = this; }

    type data;
    Node<type>* next;
    Node<type>* prev;
};

template<class type>
class CDLinkedList
{
public:
    CDLinkedList();
    ~CDLinkedList();

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
        do {
            std::cout << temp->data << ' ';
            temp = temp->next;
        } while (temp != head);
        temp = temp->prev;
        std::cout << '\n';
        do {
            std::cout << temp->data << ' ';
            temp = temp->prev;
        } while (temp != head->prev);
        std::cout << '\n';
    }

    int count;

private:
    Node<type>* head;
};

template<class type>
CDLinkedList<type>::CDLinkedList() {
    head = nullptr;
    count = 0;
}

template<class type>
CDLinkedList<type>::~CDLinkedList() {
    clear();
}

template<class type>
const type& CDLinkedList<type>::front() const {
    if (empty() == true) {
        throw std::underflow_error("List is empty");
    }
    return head->data;
}

template<class type>
const type& CDLinkedList<type>::back() const {
    if (empty() == true) {
        throw std::underflow_error("List is empty");
    }
    return head->prev->data;
}

template<class type>
void CDLinkedList<type>::push_front(const type& value) {
    Node<type>* temp = new Node<type>(value);
    if (head == nullptr) {
        head = temp;
    } else {
        temp->next = head;
        temp->prev = head->prev;
        head->prev->next = temp;
        head->prev = temp;
        head = temp;
    }
    count++;
}

template<class type>
void CDLinkedList<type>::push_back(const type& value) {
    Node<type>* temp = new Node<type>(value);
    if (head == nullptr) {
        head = temp;
    } else {
        temp->next = head;
        temp->prev = head->prev;
        head->prev->next = temp;
        head->prev = temp;
    }
    count++;
}

template<class type>
bool CDLinkedList<type>::insert_before(const type& key, const type& value) {
    bool found = false;
    Node<type>* current = head;
    do {
        if (current->data == key) {
            found = true;
            break;
        }
        current = current->next;
    } while (current != head);

    if (found == false) {
        return false;
    }

    Node<type>* temp = new Node<type>(value);
    temp->next = current;
    temp->prev = current->prev;
    current->prev->next = temp;
    current->prev = temp;
    if (current == head) {
        head = temp;
    }
    count++;
    return true;
}

template<class type>
bool CDLinkedList<type>::insert_after(const type& key, const type& value) {
    bool found = false;
    Node<type>* current = head;
    do {
        if (current->data == key) {
            found = true;
            break;
        }
        current = current->next;
    } while (current != head);

    if (found == false) {
        return false;
    }

    Node<type>* temp = new Node<type>(value);
    temp->next = current->next;
    temp->prev = current;
    current->next->prev = temp;
    current->next = temp;
    count++;
    return true;
}

template<class type>
void CDLinkedList<type>::pop_front() {
    if (head != nullptr) {
        Node<type>* temp = head;
        if (head->next == head) {
            head = nullptr;
        } else {
            head = head->next;
            head->prev = temp->prev;
            temp->prev->next = head;
        }
        count--;
        delete temp;
    }
}

template<class type>
void CDLinkedList<type>::pop_back() {
    if (head != nullptr) {
        Node<type>* temp = head->prev;
        if (head->next == head) {
            head = nullptr;
        } else {
            head->prev = temp->prev;
            temp->prev->next = head;
        }
        count--;
        delete temp;
    }
}

template<class type>
const type& CDLinkedList<type>::operator[](int index) {
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
type& CDLinkedList<type>::operator[](int index) const {
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
bool CDLinkedList<type>::erase(const type& value) {
    bool found = false;
    Node<type>* temp = head;
    do {
        if (temp->data == value) {
            found = true;
            break;
        }
        temp = temp->next;
    } while (temp != head);

    if (found == false) {
        return false;
    }

    if (temp->next == temp) {
        head = nullptr;
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        if (temp == head) {
            head = head->next;
        }
    }
    count--;
    delete temp;
    return true;
}

template<class type>
bool CDLinkedList<type>::empty() const {
    return head == nullptr;
}

template<class type>
void CDLinkedList<type>::clear() {
    while (empty() == false) {
        pop_front();
    }
}

int main() {
    CDLinkedList<int> my_list;

    my_list.push_back(1);
    my_list.push_back(2);
    my_list.push_back(3);
    my_list.push_back(4);
    my_list.push_back(5);
    my_list.push_front(0);

    my_list.insert_after(5, 43);
    my_list.insert_before(4, 22);
    
    my_list.pop_front();
    my_list.pop_back();
    my_list.erase(3);

    my_list.print();
    for (int i = 0; i < my_list.count; i++) {
        std::cout << my_list[i] << " ";
    }
    std::cout << "\nFront: " << my_list.front();
    std::cout << "\nBack: " << my_list.back();
    std::cin.get();

    return 0;
}
