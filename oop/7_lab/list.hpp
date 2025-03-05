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
    using node_allocator = typename alloc_traits::template rebind_alloc<Node>;
    using node_alloc_traits = std::allocator_traits<node_allocator>;
    using value_type = T;
    using size_type = std::size_tж
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

        template<typename... Args>
        Node(Args&&... args) : value(std::forward<Args>(args)...), prev(nullptr), next(nullptr) {}
    }

    node_allocator alloc_;
    Node* head_;
    Node* tail_;
    size_type size_;

public:


};

}


#endif // SRC_LIST__HPP