#pragma once

template <typename T>
class SmartPointer {
    T* obj;
public:
    explicit SmartPointer(T* ptr = nullptr) : obj(ptr) {}
    ~SmartPointer() { delete obj; }

    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;

    SmartPointer(SmartPointer&& other) noexcept : obj(other.obj) {
        other.obj = nullptr;
    }

    SmartPointer& operator=(SmartPointer&& other) noexcept {
        if (this != &other) {
            delete obj;
            obj = other.obj;
            other.obj = nullptr;
        }
        return *this;
    }

    inline * operator->() const { return obj; }
    inline T& operator*() const { return *obj; }
    inline T* get() const { return obj; }
};