/**
    BinarySearchTree.cpp
    Purpose: Binary Search Tree implementation in C++

    @author: Juan Castillo
    @version: 1.2 09/06/2019
*/

#include <iostream>

template<class type>
class Node
{
public:
    Node() { left = nullptr; right = nullptr; }
    Node(const type& data) { this->data = data; left = nullptr; right = nullptr; }

    type data;
    Node<type>* left;
    Node<type>* right;
};

template<class type>
class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();

    bool insert(const type& value);
    bool erase(const type& value);
    Node<type>* search(const type& value);
    void preorder_print();
    void inorder_print();
    void postorder_print();
    int height();
    void clear();

private:
    bool insert(Node<type>** leaf, const type& value);
    bool erase(Node<type>** leaf, const type& value);
    Node<type>* search(Node<type>* leaf, const type& value);
    void preorder_print(Node<type>* leaf);
    void inorder_print(Node<type>* leaf);
    void postorder_print(Node<type>* leaf);
    int height(Node<type>* leaf);
    void clear(Node<type>* leaf);

    Node<type>* root;
};

template<class type>
BinaryTree<type>::BinaryTree() {
    root = nullptr;
}

template<class type>
BinaryTree<type>::~BinaryTree() {
    clear();
}

template<class type>
bool BinaryTree<type>::insert(const type& value) {
    return insert(&root, value);
}

template<class type>
bool BinaryTree<type>::erase(const type& value) {
    return erase(&root, value);
}

template<class type>
Node<type>* BinaryTree<type>::search(const type& value) {
    return search(root, value);
}

template<class type>
void BinaryTree<type>::preorder_print() {
    preorder_print(root);
}

template<class type>
void BinaryTree<type>::inorder_print() {
    inorder_print(root);
}

template<class type>
void BinaryTree<type>::postorder_print() {
    postorder_print(root);
}

template<class type>
int BinaryTree<type>::height() {
    return height(root);
}

template<class type>
void BinaryTree<type>::clear() {
    clear(root);
    root = nullptr;
}

template<class type>
bool BinaryTree<type>::insert(Node<type>** leaf, const type& value) {
    if (*leaf == nullptr) {
        *leaf = new Node<type>(value);
        return true;
    } else if ((*leaf)->data > value) {
        return insert(&(*leaf)->left, value);
    } else if ((*leaf)->data < value) {
        return insert(&(*leaf)->right, value);
    }
    return false;
}

template<class type>
bool BinaryTree<type>::erase(Node<type>** leaf, const type& value) {
    if (*leaf != nullptr) {

        if ((*leaf)->data > value) {
            return erase(&(*leaf)->left, value);
        } else if ((*leaf)->data < value) {
            return erase(&(*leaf)->right, value);
        } else {
            Node<type>* temp = *leaf;
            if ((*leaf)->left == nullptr) {
                *leaf = (*leaf)->right;
                delete temp;
            } else if ((*leaf)->right == nullptr) {
                *leaf = (*leaf)->left;
                delete temp;
            } else {
                Node<type>* aux = (*leaf)->left;
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

template<class type>
Node<type>* BinaryTree<type>::search(Node<type>* leaf, const type& value) {
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

template<class type>
void BinaryTree<type>:: preorder_print(Node<type>* leaf) {
    if (leaf != nullptr) {
        std::cout << leaf->data << " ";
        preorder_print(leaf->left);
        preorder_print(leaf->right);
    }
}

template<class type>
void BinaryTree<type>::inorder_print(Node<type>* leaf) {
    if (leaf != nullptr) {
        inorder_print(leaf->left);
        std::cout << leaf->data << " ";
        inorder_print(leaf->right);
    }
}

template<class type>
void BinaryTree<type>::postorder_print(Node<type>* leaf) {
    if (leaf != nullptr) {
        postorder_print(leaf->left);
        postorder_print(leaf->right);
        std::cout << leaf->data << " ";
    }
}

template<class type>
int BinaryTree<type>::height(Node<type>* leaf) {
    if (leaf == nullptr) {
        return 0;
    }
    int height_left = height(leaf->left);
    int height_right = height(leaf->right);
    return 1 + (height_left > height_right ? height_left : height_right);
}

template<class type>
void BinaryTree<type>::clear(Node<type>* leaf) {
    if (leaf != nullptr) {
        clear(leaf->left);
        clear(leaf->right);
        delete leaf;
    }
}

int main() {
    BinaryTree<int> tree;

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
    std::cout << "Height: " << tree.height() << '\n';

    std::cin.get();

    return 0;
}
