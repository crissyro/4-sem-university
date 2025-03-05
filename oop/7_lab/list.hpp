#ifndef SRC_LIST__HPP
#define SRC_LIST__HPP

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace mylist {

template<typename T, typename Alloc = std::allocator<T>>
class List {
private:
    struct Node;

    using alloc_traits = std::allocator_traits<Alloc>;
    using node_allocator = typename alloc_traits::template rebind_alloc<Node>;
    using node_alloc_traits = std::allocator_traits<node_allocator>;
    
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename alloc_traits::pointer;
    using const_pointer = typename alloc_traits::const_pointer;

    class iterator;
    class const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

private:
    struct Node {
        value_type value;
        Node* prev;
        Node* next;

        template<typename... Args>
        Node(Node* p, Node* n, Args&&... args) 
            : value(std::forward<Args>(args)...), prev(p), next(n) {}
    };

    node_allocator alloc_;
    Node* head_;
    Node* tail_;
    size_type size_;

public:
    class iterator {
        Node* current_;
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit iterator(Node* node = nullptr) : current_(node) {}

        reference operator*() const { return current_->value; }
        pointer operator->() const { return &current_->value; }

        inline iterator& operator++() {
            current_ = current_->next;
            return *this;
        }

        inline iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        inline iterator& operator--() {
            current_ = current_->prev;
            return *this;
        }

        inline iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        inline bool operator==(const iterator& other) const { return current_ == other.current_; }
        inline bool operator!=(const iterator& other) const { return !(*this == other); }
    };

    class const_iterator {
        const Node* current_;
        
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = const T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        explicit const_iterator(const Node* node = nullptr) : current_(node) {}

        reference operator*() const { return current_->value; }
        pointer operator->() const { return &current_->value; }

        inline const_iterator& operator++() {
            current_ = current_->next;
            return *this;
        }

        inline const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        inline const_iterator& operator--() {
            current_ = current_->prev;
            return *this;
        }

        inline const_iterator operator--(int) {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        inline bool operator==(const const_iterator& other) const { return current_ == other.current_; }
        inline bool operator!=(const const_iterator& other) const { return !(*this == other); }
    };

    List() noexcept : alloc_(), head_(nullptr), tail_(nullptr), size_(0) {
        init_sentinels();
    }

    explicit List(const Alloc& alloc) : alloc_(alloc), head_(nullptr), tail_(nullptr), size_(0) {
        init_sentinels();
    }

    List(const List& other) : alloc_(node_alloc_traits::select_on_container_copy_construction(other.alloc_)) {
        init_sentinels();
        for(const auto& item : other) {
            push_back(item);
        }
    }

    List(List&& other) noexcept : alloc_(std::move(other.alloc_)), head_(other.head_), 
                                tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    List(std::initializer_list<value_type> init, const Alloc& alloc = Alloc()) : alloc_(alloc) {
        init_sentinels();
        for(const auto& item : init) {
            push_back(item);
        }
    }

    ~List() {
        clear();
        destroy_node(head_);
        destroy_node(tail_);
    }

    List& operator=(const List& other) {
        if(this != &other) {
            clear();
            for(const auto& item : other) {
                push_back(item);
            }
        }
        return *this;
    }

    inline iterator begin() noexcept { return iterator(head_->next); }
    inline const_iterator begin() const noexcept { return const_iterator(head_->next); }
    inline iterator end() noexcept { return iterator(tail_); }
    inline const_iterator end() const noexcept { return const_iterator(tail_); }

    inline bool empty() const noexcept { return size_ == 0; }
    inline size_type size() const noexcept { return size_; }

    void push_back(const T& value) {
        insert_node(tail_->prev, tail_, value);
    }

    void push_front(const T& value) {
        insert_node(head_, head_->next, value);
    }

    void pop_back() noexcept {
        if(!empty()) {
            Node* to_remove = tail_->prev;
            to_remove->prev->next = tail_;
            tail_->prev = to_remove->prev;
            destroy_node(to_remove);
            --size_;
        }
    }

    void clear() noexcept {
        while(!empty()) {
            pop_back();
        }
    }

private:
    void init_sentinels() {
        head_ = create_node(nullptr, nullptr);
        tail_ = create_node(head_, nullptr);
        head_->next = tail_;
        tail_->prev = head_;
    }

    Node* create_node(Node* prev, Node* next) {
        Node* node = node_alloc_traits::allocate(alloc_, 1);
        try {
            node_alloc_traits::construct(alloc_, node, prev, next);
        } catch(...) {
            node_alloc_traits::deallocate(alloc_, node, 1);
            throw;
        }

        return node;
    }

    template<typename... Args>
    Node* create_node(Node* prev, Node* next, Args&&... args) {
        Node* node = node_alloc_traits::allocate(alloc_, 1);
        try {
            node_alloc_traits::construct(alloc_, node, prev, next, std::forward<Args>(args)...);
        } catch(...) {
            node_alloc_traits::deallocate(alloc_, node, 1);
            throw;
        }

        return node;
    }

    void destroy_node(Node* node) noexcept {
        if(node) {
            node_alloc_traits::destroy(alloc_, node);
            node_alloc_traits::deallocate(alloc_, node, 1);
        }
    }

    void insert_node(Node* prev, Node* next, const T& value) {
        Node* new_node = create_node(prev, next, value);
        prev->next = new_node;
        next->prev = new_node;
        ++size_;
    }
};

} // namespace mylist

#endif // SRC_LIST__HPP