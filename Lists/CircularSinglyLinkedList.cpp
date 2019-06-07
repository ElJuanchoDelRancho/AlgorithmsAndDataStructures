/**
    CircularSinglyLinkedList.cpp
    Purpose: Circular Singly Linked List implementation in C++

    @author: Juan Castillo
    @version: 1.2 07/06/2019
*/

#include <iostream>
#include <exception>

template<class type>
class Node
{
public:
    Node() { next = this; }
    Node(const type& data) { this->data = data; next = this; }

    type data;
    Node<type>* next;
};

template<class type>
class CLinkedList
{
public:
    CLinkedList();
    ~CLinkedList();

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
        Node<type>* temp = last->next;
        do {
            std::cout << temp->data << ' ';
            temp = temp->next;
        } while (temp != last->next);
        std::cout << std::endl;
    }

    int count;

private:
    Node<type>* last;
};

template<class type>
CLinkedList<type>::CLinkedList() {
    last = nullptr;
    count = 0;
}

template<class type>
CLinkedList<type>::~CLinkedList() {
    clear();
}

template<class type>
const type& CLinkedList<type>::front() const {
    if (empty() == true) {
        throw std::underflow_error("List is empty");
    }
    return last->next->data;
}

template<class type>
const type& CLinkedList<type>::back() const {
    if (empty() == true) {
        throw std::underflow_error("List is empty");
    }
    return last->data;
}

template<class type>
void CLinkedList<type>::push_front(const type& value) {
    Node<type>* temp = new Node<type>(value);
    if (last == nullptr) {
        last = temp;
    } else {
        temp->next = last->next;
        last->next = temp;
    }
    count++;
}

template<class type>
void CLinkedList<type>::push_back(const type& value) {
    Node<type>* temp = new Node<type>(value);
    if (last == nullptr) {
        last = temp;
    } else {
        temp->next = last->next;
        last->next = temp;
        last = temp;
    }
    count++;
}

template<class type>
bool CLinkedList<type>::insert_before(const type& key, const type& value) {
    if (empty() == true) {
        return false;
    }
    bool found = false;
    Node<type> *before = last;
    do {
        if (before->next->data == key) {
            found = true;
            break;
        }
        before = before->next;
    } while (before != last);

    if (found == false) {
        return false;
    }

    Node<type>* temp = new Node<type>(value);
    temp->next = before->next;
    before->next = temp;
    count++;
    return true;
}

template<class type>
bool CLinkedList<type>::insert_after(const type& key, const type& value) {
    if (empty() == true) {
        return false;
    }
    bool found = false;
    Node<type>* current = last->next;
    do {
        if (current->data == key) {
            found = true;
            break;
        }
        current = current->next;
    } while (current != last->next);

    if (found == false) {
        return false;
    }

    Node<type>* temp = new Node<type>(value);
    temp->next = current->next;
    current->next = temp;
    if (current == last) {
        last = temp;
    }
    count++;
    return true;
}

template<class type>
void CLinkedList<type>::pop_front() {
    if (last != nullptr) {
        Node<type>* temp = last->next;
        if (last->next == last) {
            last = nullptr;
        } else {
            last->next = last->next->next;
        }
        count--;
        delete temp;
    }
}

template<class type>
void CLinkedList<type>::pop_back() {
    if (last != nullptr) {
        Node<type>* aux = last->next;
        Node<type>* temp = last;
        while(aux->next != last) {
            aux = aux->next;
        }
        if (aux == last) {
            last = nullptr;
        } else {
            aux->next = last->next;
            last = aux;
        }
        count--;
        delete temp;
    }
}

template<class type>
const type& CLinkedList<type>::operator[](int index) {
    if (index < 0 || index >= count) {
        throw std::invalid_argument("Invalid index");
    }
    Node<type>* aux = last->next;
    int aux_index = 0;
    while (aux_index < index) {
        ++aux_index;
        aux = aux->next;
    }
    return aux->data;
}

template<class type>
type& CLinkedList<type>::operator[](int index) const {
    if (index < 0 || index >= count) {
        throw std::invalid_argument("Invalid index");
    }
    Node<type>* aux = last->next;
    int aux_index = 0;
    while (aux_index < index) {
        ++aux_index;
        aux = aux->next;
    }
    return aux->data;
}

template<class type>
bool CLinkedList<type>::erase(const type& value) {
    if (empty() == true) {
        return false;
    }
    bool found = false;
    Node<type> *before = last;
    do {
        if (before->next->data == value) {
            found = true;
            break;
        }
        before = before->next;
    } while (before != last);

    if (found == false) {
        return false;
    }

    Node<type>* temp = before->next;
    if (before->next == before) {
        last = nullptr;
    } else {
        if (before->next == last) {
            last = before;
        }
        before->next = before->next->next;
    }
    count--;
    delete temp;
    return true;
}

template<class type>
bool CLinkedList<type>::empty() const {
    return last == nullptr;
}

template<class type>
void CLinkedList<type>::clear() {
    while (empty() == false) {
        pop_front();
    }
}

int main() {
    CLinkedList<int> my_list;

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
