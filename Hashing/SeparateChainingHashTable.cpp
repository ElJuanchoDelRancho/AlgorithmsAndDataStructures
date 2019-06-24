/**
    SeparateChainingHashTable.cpp
    Purpose: Hash Table implementation with separate chaining for collision handling

    @author: Juan Castillo
    @version: 1.0 24/06/2019
*/

#include <iostream>
#include <list>

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

template<class key_type, class type, int initial_size>
class HashMap
{
public:
    HashMap();
    ~HashMap();

    void insert(const key_type& key, const type& value);
    void remove(const key_type& key);
    const type& get(const key_type& key);
    void print() {
        for(int i = 0; i < initial_size; i++) {
            for (typename std::list<HashNode<key_type, type>>::iterator it = 
            table[i].begin(); it != table[i].end(); it++) {
                std::cout << "key = " << (*it).key 
                << ", value = " << (*it).value << std::endl;
            }
        }
    }

    int count;

private:
    int hash_function(const key_type& key);

    std::list<HashNode<key_type, type>>* table;
};

template<class key_type, class type, int initial_size>
HashMap<key_type, type, initial_size>::HashMap() {
    count = 0;
    table = new std::list<HashNode<key_type, type>>[initial_size];
}

template<class key_type, class type, int initial_size>
HashMap<key_type, type, initial_size>::~HashMap() {
    delete[] table;
}

template<class key_type, class type, int initial_size>
void HashMap<key_type, type, initial_size>::insert(const key_type& key, const type& value) {
    int hash_index = hash_function(key);
    for (auto x : table[hash_index]) {
        if (x.key == key) {
            return;
        }
    }
    HashNode<key_type, type> element(key, value);
    table[hash_index].push_back(element);
    count++;
}

template<class key_type, class type, int initial_size>
void HashMap<key_type, type, initial_size>::remove(const key_type& key) {
    int hash_index = hash_function(key);
    for (typename std::list<HashNode<key_type, type>>::iterator it = 
    table[hash_index].begin(); it != table[hash_index].end(); it++) {
        if ((*it).key == key) {
            table[hash_index].erase(it);
            count--;
            return;
        }
    }
}

template<class key_type, class type, int initial_size>
const type& HashMap<key_type, type, initial_size>::get(const key_type& key) {
    static type empty_value;
    int hash_index = hash_function(key);
    for (typename std::list<HashNode<key_type, type>>::iterator it = 
    table[hash_index].begin(); it != table[hash_index].end(); it++) {
        if ((*it).key == key) {
            return (*it).value;
        }
    }
    return empty_value;
}

template<class key_type, class type, int initial_size>
int HashMap<key_type, type, initial_size>::hash_function(const key_type& key) {
    return key % initial_size;
}

int main() {
    HashMap<int, int, 20> map;
    map.insert(3, 23);
    map.insert(2, 47);
    map.insert(1, 99);
    map.insert(0, 32);
    map.insert(22, 54);
    map.insert(42, 29);
    map.print();

    std::cout << map.get(22) << std::endl;
    map.remove(2);
    map.print();
    std::cin.get();

    return 0;
}
