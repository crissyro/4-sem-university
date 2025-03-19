#include "btree.hpp"


template <typename T, typename Alloc>
BTree<T, Alloc>::BTree(int order, const Alloc& alloc) 
    : t(order/2), alloc(alloc), root(nullptr) {}