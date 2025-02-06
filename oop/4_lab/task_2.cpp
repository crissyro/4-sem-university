#include <iostream>
#include <memory>
#include <cstring>
#include <algorithm>


template <typename Alloc = std::allocator<char>>
class String_ {
    using alloc_traits = std::allocator_traits<Alloc>;

private:
    char* str;
    size_t length;
    Alloc allocator_;

    void free() {
        if (str) {
            allocator_.deallocate(str, length + 1); 
            str = nullptr;
            length = 0;
        }
    }

    void reallocate(size_t new_size) {
        char* new_str = allocator_.allocate(new_size + 1); 
        std::memcpy(new_str, str, length);
        free();

        str = new_str;
        length = new_size;
    }

    void copyChars(const char* src, size_t n) {
        reallocate(n);
        std::memcpy(str, src, n);
        str[n] = '\0';
    }

    void appendChars(const char* src, size_t n) {
        reallocate(length + n);
        std::memcpy(str + length, src, n);
        length += n;
        str[length] = '\0';
    }

    void appendChar(char c) {
        reallocate(length + 1);
        str[length++] = c;
        str[length] = '\0';
    }

    void appendString(const String_& other) { appendChars(other.str, other.length); }

    void appendCString(const char* src) { appendChars(src, std::strlen(src)); }

    void insertChars(size_t pos, const char* src, size_t n) {
        reallocate(length + n);
        std::memmove(str + pos + n, str + pos, length - pos);
        std::memcpy(str + pos, src, n);
        length += n;
        str[length] = '\0';
    }

    void erase(size_t pos, size_t n) {
        if (pos + n > length) n = length - pos;
        std::memmove(str + pos, str + pos + n, length - (pos + n));
        length -= n;
        str[length] = '\0';
    }

    void replace(size_t pos, size_t n, const char* src, size_t m) {
        erase(pos, n);
        insertChars(pos, src, m);
    }

    inline int compare(const String_& other) const { return std::strcmp(str, other.str); }

public:
    String_() : str(nullptr), length(0) {}

    String_(const char* s) : str(nullptr), length(0) {
        copyChars(s, std::strlen(s));
    }

    String_(const String_& other) : str(nullptr), length(0), allocator_(other.allocator_) {
        copyChars(other.str, other.length);
    }

    String_(String_&& other) noexcept : str(other.str), length(other.length), allocator_(std::move(other.allocator_)) {
        other.str = nullptr;
        other.length = 0;
    }

    ~String_() { free(); }

    inline size_t count_spaces() const { return std::count(str, str + length, ' '); }

    inline void to_lower_case() {
        for (size_t i = 0; i < length; ++i) str[i] = std::tolower(str[i]);
    }

    void remove_punctuation_marks() {
        size_t newLength = 0;
        for (size_t i = 0; i < length; ++i) {
            if (!std::ispunct(str[i])) 
                str[newLength++] = str[i];
        }

        length = newLength;
        str[length] = '\0';
    }

    String_ operator/(size_t divisor) const {
        size_t newLength = length / divisor
        ;
        String_ result;
        result.copyChars(str, newLength);

        return result;
    }

    String_ operator>>(size_t n) const {
        if (n >= length) return String_();

        String_ result;
        result.copyChars(str + n, length - n);

        return result;
    }

    inline friend std::ostream& operator<<(std::ostream& os, const String_& str_obj) {
        os << str_obj.str;
        return os;
    }

    inline size_t size() const { return length; }

    inline const char* c_str() const { return str; }
};

int main() {
    String_<> s("Hello, World! ZXC raddan, international winner !!! I AM KAGGLE EXPERT");
    std::cout << "Строка: " << s << "\n";
    
    std::cout << "\nКол-во пробелов: " << s.count_spaces() << "\n";
    
    s.to_lower_case();
    std::cout << "\nНижний регистр: " << s << "\n";
    
    s.remove_punctuation_marks();
    std::cout << "\nУдаление знаков препинания: " << s << "\n";
    
    String_<> s2 = s / 2;
    std::cout << "\nДеление длины на 2: " << s2 << "\n";
    
    String_<> s3 = s >> 3;
    std::cout << "\nСдвиг вправо на 3: " << s3 << "\n";

    return 0;
}
