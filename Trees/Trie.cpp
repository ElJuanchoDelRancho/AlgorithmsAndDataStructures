/**
    Trie.cpp
    Purpose: Trie implementation in C++ with only lower case

    @author: Juan Castillo
    @version: 1.0 25/06/2019
*/

#include <iostream>
#include <string>

const int ALPHABET_SIZE = 26;

class TrieNode
{
public:
    TrieNode() {
        end_of_word = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }

    TrieNode* children[ALPHABET_SIZE];
    bool end_of_word;
};

class Trie
{
public:
    Trie();
    ~Trie();

    void insert(std::string key);
    bool search(std::string key);
    void remove(std::string key);
    void clear();

private:
    TrieNode* remove(std::string key, TrieNode* node, int character = 0);
    void clear(TrieNode* node);
    bool empty(TrieNode* node);

    TrieNode* root;
};

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    clear(root);
}

void Trie::insert(std::string key) {
    TrieNode* aux = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (aux->children[index] == nullptr) {
            aux->children[index] = new TrieNode();
        }
        aux = aux->children[index];
    }
    aux->end_of_word = true;
}

bool Trie::search(std::string key) {
    TrieNode* aux = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (aux->children[index] == nullptr) {
            return false;
        }
        aux = aux->children[index];
    }
    return aux->end_of_word;
}

void Trie::remove(std::string key) {
    remove(key, root);
}

TrieNode* Trie::remove(std::string key, TrieNode* node, int character) {
    if (node == nullptr) {
        return nullptr;
    }
    if (character == key.length()) {
        if (node->end_of_word == true) {
            node->end_of_word = false;
        }
        if (empty(node) == true) {
            delete node;
            node = nullptr;
        }
        return node;
    }
    int index = key[character] - 'a'; 
    node->children[index] = remove(key, node->children[index], character + 1);
    if (empty(node) == true && node->end_of_word == false && node != root) {
        delete node;
        node = nullptr;
    }
    return node; 
}

bool Trie::empty(TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != nullptr) {
            return false;
        }
    }
    return true;
}

void Trie::clear() {
    clear(root);
}

void Trie::clear(TrieNode* node) {
    if (node != nullptr) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            clear(node->children[i]);
        }
        delete node;
    }
}

int main() {
    std::string keys[] = {"the", "a", "there", 
                            "answer", "any", "by", 
                            "bye", "their" }; 
    int tam = sizeof(keys) / sizeof(keys[0]);
    Trie my_trie;

    for (int i = 0; i < tam; i++) {
        my_trie.insert(keys[i]);
    }

    std::cout << "Is the word \"the\" in the trie?: " 
        << (my_trie.search("the") ? "Yes\n" : "No\n");
    std::cout << "Is the word \"these\" in the trie?: " 
        << (my_trie.search("these") ? "Yes\n" : "No\n");
    my_trie.remove("the");
    std::cout << "Is the word \"the\" in the trie?: " 
        << (my_trie.search("the") ? "Yes\n" : "No\n");
    std::cin.get();

    return 0;
}
