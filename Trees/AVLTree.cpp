/**
    AVLTree.cpp
    Purpose: AVL Tree implementation in C++

    @author: Juan Castillo
    @version: 1.0 09/06/2019
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
class AVLTree
{
public:
    AVLTree();
    ~AVLTree();

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

    int balance(Node<type>* leaf);
    Node<type>* left_rotation(Node<type>* leaf);
    Node<type>* right_rotation(Node<type>* leaf);

    Node<type>* root;
};

template<class type>
AVLTree<type>::AVLTree() {
    root = nullptr;
}

template<class type>
AVLTree<type>::~AVLTree() {
    clear();
}

template<class type>
bool AVLTree<type>::insert(const type& value) {
    return insert(&root, value);
}

template<class type>
bool AVLTree<type>::erase(const type& value) {
    return erase(&root, value);
}

template<class type>
Node<type>* AVLTree<type>::search(const type& value) {
    return search(root, value);
}

template<class type>
void AVLTree<type>::preorder_print() {
    preorder_print(root);
}

template<class type>
void AVLTree<type>::inorder_print() {
    inorder_print(root);
}

template<class type>
void AVLTree<type>::postorder_print() {
    postorder_print(root);
}

template<class type>
int AVLTree<type>::height() {
    return height(root);
}

template<class type>
void AVLTree<type>::clear() {
    clear(root);
    root = nullptr;
}

template<class type>
bool AVLTree<type>::insert(Node<type>** leaf, const type& value) {
    bool was_inserted = false;
    
    if (*leaf == nullptr) {
        *leaf = new Node<type>(value);
        was_inserted = true;
    } else if ((*leaf)->data > value) {
        was_inserted = insert(&(*leaf)->left, value);
    } else if ((*leaf)->data < value) {
        was_inserted = insert(&(*leaf)->right, value);
    } else {
        was_inserted = false;
    }

    if (was_inserted == false) {
        return false;
    }

    int balance_factor = balance(*leaf);

    if (balance_factor > 1 && value > (*leaf)->right->data) { // Case RR
        *leaf = left_rotation(*leaf);
    } else if (balance_factor > 1) { // Case RL
        (*leaf)->right = right_rotation((*leaf)->right);
        *leaf = left_rotation(*leaf);
    } else if (balance_factor < -1 && value < (*leaf)->left->data) { // Case LL
        *leaf = right_rotation(*leaf);
    } else if (balance_factor < -1) { // Case LR
        (*leaf)->left = left_rotation((*leaf)->left);
        *leaf = right_rotation(*leaf);
    }

    return was_inserted;
}

template<class type>
bool AVLTree<type>::erase(Node<type>** leaf, const type& value) {
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

            if (root == nullptr) {
                return true;
            }

            int balance_factor = balance(*leaf);
            if (balance_factor > 1 && value > (*leaf)->right->data) { // Case RR
                *leaf = left_rotation(*leaf);
            } else if (balance_factor > 1) { // Case RL
                (*leaf)->right = right_rotation((*leaf)->right);
                *leaf = left_rotation(*leaf);
            } else if (balance_factor < -1 && value < (*leaf)->left->data) { // Case LL
                *leaf = right_rotation(*leaf);
            } else if (balance_factor < -1) { // Case LR
                (*leaf)->left = left_rotation((*leaf)->left);
                *leaf = right_rotation(*leaf);
            }
            return true;
        }

    }
    return false;
}

template<class type>
Node<type>* AVLTree<type>::search(Node<type>* leaf, const type& value) {
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
void AVLTree<type>:: preorder_print(Node<type>* leaf) {
    if (leaf != nullptr) {
        std::cout << leaf->data << " ";
        preorder_print(leaf->left);
        preorder_print(leaf->right);
    }
}

template<class type>
void AVLTree<type>::inorder_print(Node<type>* leaf) {
    if (leaf != nullptr) {
        inorder_print(leaf->left);
        std::cout << leaf->data << " ";
        inorder_print(leaf->right);
    }
}

template<class type>
void AVLTree<type>::postorder_print(Node<type>* leaf) {
    if (leaf != nullptr) {
        postorder_print(leaf->left);
        postorder_print(leaf->right);
        std::cout << leaf->data << " ";
    }
}

template<class type>
int AVLTree<type>::height(Node<type>* leaf) {
    if (leaf == nullptr) {
        return 0;
    }
    int height_left = height(leaf->left);
    int height_right = height(leaf->right);
    return 1 + (height_left > height_right ? height_left : height_right);
}

template<class type>
void AVLTree<type>::clear(Node<type>* leaf) {
    if (leaf != nullptr) {
        clear(leaf->left);
        clear(leaf->right);
        delete leaf;
    }
}

template<class type>
int AVLTree<type>::balance(Node<type>* leaf) {
    if (leaf == nullptr) {
        return 0;
    }
    return height(leaf->right) - height(leaf->left);
}

template<class type>
Node<type>* AVLTree<type>::left_rotation(Node<type>* leaf) {
    Node<type>* new_root = leaf->right;
    leaf->right = new_root->left;
    new_root->left = leaf;
    return new_root;
}

template<class type>
Node<type>* AVLTree<type>::right_rotation(Node<type>* leaf) {
    Node<type>* new_root = leaf->left;
    leaf->left = new_root->right;
    new_root->right = leaf;
    return new_root;
}

int main() {
    AVLTree<int> tree;
    
    tree.insert(65);
    tree.insert(74);
    tree.insert(50);
    tree.insert(41);
    tree.insert(46);
    tree.insert(70);
    tree.insert(97);
    tree.insert(54);
    tree.insert(17);

    tree.inorder_print();
    tree.erase(74);
    tree.erase(70);
    std::cout << '\n';
    tree.inorder_print();

    std::cin.get();

    return 0;
}
