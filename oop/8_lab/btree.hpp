#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>


#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T, typename Alloc = std::allocator<T>>
class BTree {
private:
    struct Node;
    using NodeAlloc = typename Alloc::template rebind<Node>::other;
    
    NodeAlloc alloc;
    Node* root;
    const int t;

    void splitChild(Node* parent, int index);
    void insertNonFull(Node* node, const T& key);
    void deleteNode(Node* node);
    void balance(Node* node);
    void borrowFromPrev(Node* node, int index);
    void borrowFromNext(Node* node, int index);
    void merge(Node* node, int index);
    T getPredecessor(Node* node, int index);
    T getSuccessor(Node* node, int index);
    void fill(Node* node, int index);
    void removeFromLeaf(Node* node, int index);
    void removeFromNonLeaf(Node* node, int index);
    Node* search(Node* node, const T& key) const;

public:
    explicit BTree(int order = 4, const Alloc& alloc = Alloc());
    ~BTree();
    
    void insert(const T& key);
    void erase(const T& key);
    bool contains(const T& key) const;
    void print() const;
};

template <typename T, typename Alloc>
struct BTree<T, Alloc>::Node {
    bool is_leaf;
    std::vector<T, Alloc> keys;
    std::vector<Node*, typename Alloc::template rebind<Node*>::other> children;

    Node(bool leaf, const Alloc& alloc) 
        : is_leaf(leaf), keys(alloc), children(alloc) {}
};
