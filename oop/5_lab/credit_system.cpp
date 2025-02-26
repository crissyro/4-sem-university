#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

class Date {
private:
    u_int32_t day, month, year;

public:
    Date(u_int32_t d, u_int32_t m, u_int32_t y) : day(d), month(m), year(y) {}

    inline u_int32_t getDay() const { return day; }
    inline u_int32_t getMonth() const { return month; }
    inline u_int32_t getYear() const { return year; }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
};

class Client {
public: 
    virtual ~Client() = default;
    virtual void printInfo() const = 0;
    virtual bool isCriteria() const = 0;
};



int main () {

    return 0;
}