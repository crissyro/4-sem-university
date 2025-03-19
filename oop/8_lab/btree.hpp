#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>


template <typename T>
class BTreeNode {
private:
    bool is_leaf_;
    std::vector<T> keys_;
    std::vector<std::unique_ptr<BTreeNode>> children_;

public:
    explicit BTreeNode(bool is_leaf = true) : is_leaf_(is_leaf) {}

    ~BTreeNode() = default;

    inline bool is_leaf() const { 
        return is_leaf_; 
    }

    inline const std::vector<T>& keys() const { 
        return keys_; 
    }

    inline size_t num_keys() const { 
        return keys_.size(); 
    }

    inline const std::unique_ptr<BTreeNode>& child(size_t index) const { 
        return children_[index]; 
    }

    inline void insert_key(size_t index, const T& key) { 
        keys_.insert(keys_.begin() + index, key); 
    }

    inline void erase_key(size_t index) { 
        keys_.erase(keys_.begin() + index); 
    }
    
    inline void add_child(size_t index, std::unique_ptr<BTreeNode> child) { 
        children_.insert(children_.begin() + index, std::move(child)); 
    }

    inline void remove_child(size_t index) { 
        children_.erase(children_.begin() + index); 
    }
};