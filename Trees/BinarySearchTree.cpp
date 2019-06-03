/**
    BinarySearchTree.cpp
    Purpose: Binary Search Tree implementation in C++

    @author: Juan Castillo
    @version: 1.1 02/06/2019
*/

#include <iostream>

class Node
{
public:
    Node() { left = nullptr; right = nullptr; }
    Node(int data) { this->data = data; left = nullptr; right = nullptr; }

    int data;
    Node* left;
    Node* right;
};

class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();

    bool insert(int value);
    bool erase(int value);
    Node* search(int value);
    void preorder_print();
    void inorder_print();
    void postorder_print();
    void clear();

private:
    bool insert(Node** leaf, int value);
    bool erase(Node** leaf, int value);
    Node* search(Node* leaf, int value);
    void preorder_print(Node* leaf);
    void inorder_print(Node* leaf);
    void postorder_print(Node* leaf);
    void clear(Node* leaf);

    Node* root;
};

BinaryTree::BinaryTree() {
    root = nullptr;
}

BinaryTree::~BinaryTree() {
    clear();
}

bool BinaryTree::insert(int value) {
    return insert(&root, value);
}

bool BinaryTree::erase(int value) {
    return erase(&root, value);
}

Node* BinaryTree::search(int value) {
    return search(root, value);
}

void BinaryTree::preorder_print() {
    preorder_print(root);
}

void BinaryTree::inorder_print() {
    inorder_print(root);
}

void BinaryTree::postorder_print() {
    postorder_print(root);
}

void BinaryTree::clear() {
    clear(root);
    root = nullptr;
}

bool BinaryTree::insert(Node** leaf, int value) {
    if (*leaf == nullptr) {
        *leaf = new Node(value);
        return true;
    } else if ((*leaf)->data > value) {
        return insert(&(*leaf)->left, value);
    } else if ((*leaf)->data < value) {
        return insert(&(*leaf)->right, value);
    }
    return false;
}

bool BinaryTree::erase(Node** leaf, int value) {
    if (*leaf != nullptr) {

        if ((*leaf)->data > value) {
            return erase(&(*leaf)->left, value);
        } else if ((*leaf)->data < value) {
            return erase(&(*leaf)->right, value);
        } else {
            Node* temp = *leaf;
            if ((*leaf)->left == nullptr) {
                *leaf = (*leaf)->right;
                delete temp;
            } else if ((*leaf)->right == nullptr) {
                *leaf = (*leaf)->left;
                delete temp;
            } else {
                Node *aux = (*leaf)->left;
                while (aux->right != nullptr) {
                    aux = aux->right;
                }
                (*leaf)->data = aux->data;
                erase(&(*leaf)->left, aux->data);
            }
            return true;
        }

    } else {
        return false;
    }
}

Node* BinaryTree::search(Node* leaf, int value) {
    if (leaf != nullptr) {
        if (leaf->data > value) {
            return search(leaf->left, value);
        } else if (leaf->data < value) {
            return search(leaf->right, value);
        } else {
            return leaf;
        }
    }
    return nullptr;
}

void BinaryTree:: preorder_print(Node* leaf) {
    if (leaf != nullptr) {
        std::cout << leaf->data << " ";
        preorder_print(leaf->left);
        preorder_print(leaf->right);
    }
}

void BinaryTree::inorder_print(Node* leaf) {
    if (leaf != nullptr) {
        inorder_print(leaf->left);
        std::cout << leaf->data << " ";
        inorder_print(leaf->right);
    }
}

void BinaryTree::postorder_print(Node* leaf) {
    if (leaf != nullptr) {
        postorder_print(leaf->left);
        postorder_print(leaf->right);
        std::cout << leaf->data << " ";
    }
}

void BinaryTree::clear(Node* leaf) {
    if (leaf != nullptr) {
        clear(leaf->left);
        clear(leaf->right);
        delete leaf;
    }
}

int main() {
    BinaryTree tree;

    tree.insert(10);
    tree.insert(8);
    tree.insert(9);
    tree.insert(34);
    tree.insert(3);
    tree.insert(15);
    tree.insert(17);
    
    tree.erase(10);

    tree.preorder_print();
    std::cout << std::endl;
    tree.inorder_print();
    std::cout << std::endl;
    tree.postorder_print();
    std::cout << std::endl;

    std::cin.get();

    return 0;
}
