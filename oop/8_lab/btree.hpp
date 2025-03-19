#pragma once

#include <vector>
#include <memory>
#include <algorithm>


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
    void balance(Node* node);
    void deleteNode(Node* node);

public:
    explicit BTree(int order = 4, const Alloc& alloc = Alloc());
    
    ~BTree();
    
    void insert(const T& key);
    void erase(const T& key);
    bool search(const T& key) const;
    void print() const;
};

template <typename T, typename Alloc>
struct BTree<T, Alloc>::Node {
    bool is_leaf;
    std::vector<T, Alloc> keys;
    std::vector<Node*> children;

    Node(bool leaf, const Alloc& alloc) 
        : is_leaf(leaf), keys(alloc), children(alloc) {}
};