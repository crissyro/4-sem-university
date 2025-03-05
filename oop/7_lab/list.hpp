#ifndef SRC_LIST__HPP
#define SRC_LIST__HPP

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <stdexcept>


namespace mylist {

template<typename T, typename Alloc = std::allocator<T>>
class List {
private:    
    using alloc_traits = std::allocator_traits<Alloc>;
    using value_type = T;
    using size_type = std::size_t
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename alloc_traits::pointer;
    using const_pointer = typename alloc_traits::const_pointer;
    using iterator = *T;
    using const_iterator = const *T;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    struct Node {
        value_type value;
        Node* prev;
        Node* next;
        Node() : prev(nullptr), next(nullptr) {}
        Node(value_type&& val, Node* p = nullptr, Node* n = nullptr) : value(std::move(val)), prev(p), next(n) {}
        Node(const value_type& val, Node* p = nullptr, Node* n = nullptr) : value(val), prev(p), next(n) {}
        ~Node() {
            if (prev) prev->next = next;
            if (next) next->prev = prev;
            alloc_traits::destroy(allocator, &value);
            alloc_traits::deallocate(allocator, this, 1);
        }
    }

    Alloc allocator;
    Node* head;
    Node* tail;

public:


};

}


#endif // SRC_LIST__HPP