#include "btree.hpp"


template <typename T, typename Alloc>
BTree<T, Alloc>::BTree(int order, const Alloc& alloc) 
    : t(order/2), alloc(alloc), root(nullptr) {}

template <typename T, typename Alloc>
BTree<T, Alloc>::~BTree() {
    if(root) {
        deleteNode(root);
        alloc.destroy(root);
        alloc.deallocate(root, 1);
    }
}

template <typename T, typename Alloc>
void BTree<T, Alloc>::deleteNode(Node* node) {
    if(!node->is_leaf) {
        for(auto child : node->children) {
            deleteNode(child);
            alloc.destroy(child);
            alloc.deallocate(child, 1);
        }
    }
}

template <typename T, typename Alloc>
void BTree<T, Alloc>::insert(const T& key) {
    if(!root) {
        root = alloc.allocate(1);
        alloc.construct(root, true, alloc);
        root->keys.push_back(key);
        return;
    }

    if(root->keys.size() == 2*t-1) {
        Node* new_root = alloc.allocate(1);
        alloc.construct(new_root, false, alloc);
        new_root->children.push_back(root);
        splitChild(new_root, 0);
        root = new_root;
    }
    
    insertNonFull(root, key);
}