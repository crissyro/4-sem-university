#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <utility>

template <typename T>
class SmartPointer {
    T* ptr;
    
public:
    explicit SmartPointer(T* p = nullptr) noexcept : ptr(p) {}
    
    SmartPointer(SmartPointer&& other) noexcept : ptr(other.release()) {}
    
    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;

    ~SmartPointer() { reset(); }

    SmartPointer& operator=(SmartPointer&& other) noexcept {
        reset(other.release());
        return *this;
    }

    T* operator->() const noexcept { 
        return ptr; 
    }

    T& operator*() const noexcept { 
        return *ptr; 
    }

    explicit operator bool() const noexcept { 
        return ptr != nullptr; 
    }

    void reset(T* p = nullptr) noexcept {
        delete ptr;
        ptr = p;
    }
    
    T* release() noexcept {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void swap(SmartPointer& other) noexcept {
        using std::swap;
        swap(ptr, other.ptr);
    }

    T* get() const noexcept { 
        return ptr; 
    }
};

template <typename T>
class SmartPointer<T[]> {
    T* ptr;
    
public:
    explicit SmartPointer(T* p = nullptr) noexcept : ptr(p) {}

    ~SmartPointer() { 
        delete[] ptr; 
    }
    
    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;
    
    SmartPointer(SmartPointer&& other) noexcept : ptr(other.release()) {}
    SmartPointer& operator=(SmartPointer&& other) noexcept {
        reset(other.release());
        return *this;
    }
    
    T& operator[](size_t index) const { return ptr[index]; }
    void reset(T* p = nullptr) noexcept {
        delete[] ptr;
        ptr = p;
    }

    T* release() noexcept {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
};

template <typename T, typename... Args>
SmartPointer<T> MakeSmart(Args&&... args) {
    return SmartPointer<T>(new T(std::forward<Args>(args)...));
}

#endif // SMARTPOINTER_H
