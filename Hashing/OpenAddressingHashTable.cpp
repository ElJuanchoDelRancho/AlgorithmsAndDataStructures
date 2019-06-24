/**
    OpenAddressingHashTable.cpp
    Purpose: Hash Table implementation with open addressing for collision handling

    @author: Juan Castillo
    @version: 1.0 24/06/2019
*/

#include <iostream>

template<class key_type, class type>
class HashNode
{
public:
    key_type key;
    type value;
    HashNode() { }
    HashNode(const key_type& key_p, const type& value_p) {
        key = key_p;
        value = value_p;
    }
};

template<class key_type, class type, int size>
class HashMap
{
public:
    HashMap();
    ~HashMap();

    void insert(const key_type& key, const type& value);
    void remove(const key_type& key);
    const type& get(const key_type& key);
    void print() {
        for(int i = 0; i < capacity; i++) {
            if(table[i] != nullptr && table[i]->key != -1)
                std::cout << "key = " << table[i]->key 
                << ", value = " << table[i]->value << std::endl;
        }
    }

    int count;
    int capacity;

private:
    int hash_function(const key_type& key);

    HashNode<key_type, type>** table;
};

template<class key_type, class type, int size>
HashMap<key_type, type, size>::HashMap() {
    capacity = size;
    count = 0;
    table = new HashNode<key_type, type>*[size];
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

template<class key_type, class type, int size>
HashMap<key_type, type, size>::~HashMap() {
    for (int i = 0; i < size; i++) {
        if (table[i] != nullptr) {
            delete table[i];
        }
    }
    delete[] table;
}

template<class key_type, class type, int size>
void HashMap<key_type, type, size>::insert(const key_type& key, const type& value) {
    if (count != capacity) {
        int hash_index = hash_function(key);
        int counter = 0;

        while (table[hash_index] != nullptr && table[hash_index]->key != key
        && table[hash_index]->key != -1 && counter != capacity) {
            hash_index++;
            hash_index %= capacity;
            counter++;
        }
        if (table[hash_index] == nullptr || table[hash_index]->key == -1) {
            count++;
            table[hash_index] = new HashNode<key_type, type>(key, value);
        }
    }
}

template<class key_type, class type, int size>
void HashMap<key_type, type, size>::remove(const key_type& key) {
    int hash_index = hash_function(key);
    int counter = 0;

    while (table[hash_index] != nullptr && counter != capacity) {
        if (table[hash_index]->key == key) {
            delete table[hash_index];
            table[hash_index] = new HashNode<key_type, type>(-1, -1);
            count--;
        }
        hash_index++;
        hash_index %= capacity;
        counter++;
    }
}

template<class key_type, class type, int size>
const type& HashMap<key_type, type, size>::get(const key_type& key) {
    static type empty_value;
    int hash_index = hash_function(key);
    int counter = 0;

    while (table[hash_index] != nullptr && counter != capacity) {
        if (table[hash_index]->key == key) {
            return table[hash_index]->value;
        }
        hash_index++;
        hash_index %= capacity;
        counter++;
    }
    return empty_value;
}

template<class key_type, class type, int size>
int HashMap<key_type, type, size>::hash_function(const key_type& key) {
    return key % size;
}

int main() {
    HashMap<int, int, 20> map;
    map.insert(3, 23);
    map.insert(2, 47);
    map.insert(1, 99);
    map.insert(0, 32);
    map.insert(22, 54);
    map.print();

    std::cout << map.get(22) << std::endl;
    map.remove(2);
    std::cout << map.get(2) << std::endl;
    std::cin.get();

    return 0;
}
