#include <iostream>
#include <vector>
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

    inline bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }
};

class Client {
public: 
    virtual ~Client() = default;
    virtual void printInfo() const = 0;
    virtual bool isCriteria(const Date& targetDate) const = 0;
};

class Depositor: public Client {
private:
    std::string surname;
    Date depositDate;
    u_int64_t depositAmount;
    _Float64 interestRate;

public:
    Depositor(const std::string& n, const Date& d, u_int64_t a, _Float64 r) : 
            surname(n), depositDate(d), depositAmount(a), interestRate(r) {}

    void printInfo() const override {
        std::cout << "Тип: Вкладчик\nФамилия: " << surname
        << "\nДата открытия: " << std::setfill('0') 
        << std::setw(2) << depositDate.getDay() << "."
        << std::setw(2) << depositDate.getMonth() << "."
        << depositDate.getYear() << "\nСумма: " << depositAmount
        << "\nПроцентная ставка: " << interestRate << "%\n\n";
    }

    inline bool isCriteria(const Date& targetDate) const override { return depositDate == targetDate; }
};

class Creditor : public Client {
private:
    std::string surname;
    Date creditDate;
    u_int64_t amount;
    _Float64 interestRate;
    _Float64 remainingDebt;

public:
    Creditor(const std::string& s, const Date& d, u_int64_t a, _Float64 ir, _Float64 rd) : 
        surname(s), creditDate(d), amount(a), interestRate(ir), remainingDebt(rd) {}

    void printInfo() const override {
        std::cout << "Тип: Кредитор\nФамилия: " << surname
            << "\nДата выдачи: " << std::setfill('0')
            << std::setw(2) << creditDate.getDay() << "."
            << std::setw(2) << creditDate.getMonth() << "."
            << creditDate.getYear() << "\nСумма: " << amount
            << "\nПроцентная ставка: " << interestRate << "%"
            << "\nОстаток долга: " << remainingDebt << "\n\n";
    }

    inline bool isCriteria(const Date& targetDate) const override { return creditDate == targetDate; }
};

class Organization : public Client {
    std::string name;
    Date accountDate;
    std::string accountNumber;
    _Float64 balance;

public:
    Organization(std::string n, Date d, std::string an, double b)
        : name(n), accountDate(d), accountNumber(an), balance(b) {}

    void printInfo() const override {
        std::cout << "Тип: Организация\nНазвание: " << name
             << "\nДата открытия: " << std::setfill('0')
             << std::setw(2) << accountDate.getDay() << "."
             << std::setw(2) << accountDate.getMonth() << "."
             << accountDate.getYear() << "\nНомер счёта: " << accountNumber
             << "\nБаланс: " << balance << "\n\n";
    }

    inline bool isCriteria(const Date& targetDate) const override { return accountDate == targetDate; }
};

class ClientsBase {
private: 
    std::vector<Client*> clients;

public:
    ClientsBase(const std::vector<Client*>& clients_) : clients(clients_) {}
    ClientsBase(ClientsBase&& other) noexcept : clients(std::move(other.clients)) {}

    inline void printClients() const {
        std::cout << "Все клиенты:\n";
        for (const auto& client : clients) { 
            client->printInfo(); 
        }
    }

    inline void printTargetClients(Date& targetDate) const {
        printf("\nКлиенты с датой %d.%d.%d:\n", targetDate.getDay(), targetDate.getMonth(), targetDate.getYear());
        for (const auto& client : clients) { 
            if (client->isCriteria(targetDate)) { 
                client->printInfo(); 
            }
        }
    }
    void addClient(Client* client) { clients.push_back(client); }

    ~ClientsBase() {
        for (auto& client : clients) {
            delete client;
        }
    }
};

int main() {
    std::vector<Client*> clients = {
        new Depositor("Иваныч", {15, 5, 2025}, 510, 5.5),
        new Creditor("Петрова", {15, 10, 2023}, 4000000, 7.0, 50000),
        new Depositor("Сидорова", {10, 8, 2024}, 3500000, 6.2),
        new Creditor("Левина", {10, 7, 2022}, 3000000, 6.8, 100000),
        new Creditor("Мороз", {20, 6, 2021}, 1000000, 7.2, 250000),
        new Organization("ООО \'БНАЛ\'", {10, 1, 2022}, "40702810500000000001", 2500000),
        new Depositor("Мавроди", {15, 5, 2020}, 750000, 6.0)
    };

    ClientsBase clientsBase(clients);
    clientsBase.printClients();
    Date targetDate(15, 5, 2025);
    clientsBase.printTargetClients(targetDate);

    return 0;
}